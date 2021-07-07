#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>

#include <boost/program_options.hpp>

#include <SFML/Graphics.hpp>

#include "cellular_automata_engine.hpp"
#include "cellular_automaton.hpp"
#include "kcav.hpp"
#include "life_ruleset.hpp"
#include "sfml_err_redirector.hpp"
#include "wrapping_neighbors_selector.hpp"

namespace kcav
{
	std::vector<sf::Vector2<int>> kcav::mooreNeighbors(
		{
			{0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}
		});

	std::vector<sf::Vector2<int>> kcav::vonNeumannNeighbors(
		{
			{0, -1}, {1, 0}, {0, 1}, {-1, 0},
			{0, -2}, {2, 0}, {0, 2}, {-2, 0}
		});

	kcav::kcav() : options("Options"), hiddenOptions("Hidden Options"), visibleOptions("Options")
	{
		setup_options();
	}

	int kcav::run(int argc, char* argv[])
	{
		sfml_err_redirector errDisabler(NULL);

		if (!process_option_storage(argc, argv))
		{
			return EXIT_FAILURE;
		}

		// Process the secondary usages before trying to use primary arguments.
		if (process_secondary_usages())
		{
			return EXIT_SUCCESS;
		}

		if (!process_options_notification())
		{
			return EXIT_FAILURE;
		}

		if (!setup_cellular_automaton())
		{
			print_invalid_identifier_error_message();

			return EXIT_FAILURE;
		}

		if (!load_image_file())
		{
			print_file_load_error_message();

			return EXIT_FAILURE;
		}

		if (!setup_generation_time())
		{
			print_invalid_time_error_message();

			return EXIT_FAILURE;
		}

		run_engine_loop();

		return EXIT_SUCCESS;
	}

	void kcav::setup_options()
	{
		setup_hidden_options();
		setup_visible_options();
		setup_positional_options();

		options.add(visibleOptions).add(hiddenOptions);
	}

	void kcav::setup_hidden_options()
	{
		hiddenOptions.add_options()
			("help", "print help information")
			("version", "print version information")
			("ruleset", boost::program_options::value<std::string>()->required(), "cellular automaton ruleset identifier")
			("image-path", boost::program_options::value<std::string>()->required(), "input image path");
	}

	void kcav::setup_visible_options()
	{
		visibleOptions.add_options()
			("time,t", boost::program_options::value<int>()->default_value(100), "amount of miliseconds between each generation");
	}

	void kcav::setup_positional_options()
	{
		positionalOptions.add("ruleset", 1).add("image-path", 1);
	}

	void kcav::store_options(int argc, char* argv[])
	{
		boost::program_options::parsed_options parsedOptions = boost::program_options::command_line_parser(argc, argv).options(options).positional(positionalOptions).run();

		boost::program_options::store(parsedOptions, optionsMap);
	}

	bool kcav::setup_cellular_automaton()
	{
		std::string rulesetIdentifier = optionsMap["ruleset"].as<std::string>();
		std::unique_ptr<ruleset> ruleset;
		std::unique_ptr<neighbors_selector> neighborsSelector;

		if (rulesetIdentifier == "life")
		{
			ruleset = std::make_unique<life_ruleset>();
			neighborsSelector = std::make_unique<wrapping_neighbors_selector>(mooreNeighbors);
		}
		else
		{
			return false;
		}

		cellularAutomaton = std::make_unique<cellular_automaton>(std::move(ruleset), std::move(neighborsSelector));

		return true;
	}

	bool kcav::setup_generation_time()
	{
		int time = optionsMap["time"].as<int>();

		if (time < 0)
		{
			return false;
		}

		millisecondsPerGeneration = time;

		return true;
	}

	bool kcav::process_option_storage(int argc, char* argv[])
	{
		try
		{
			store_options(argc, argv);
		}
		catch (...)
		{
			handle_program_options_exceptions();

			return false;
		}

		return true;
	}

	bool kcav::process_secondary_usages() const
	{
		if (optionsMap.count("help") > 0)
		{
			print_help_message();

			return true;
		}

		if (optionsMap.count("version") > 0)
		{
			print_version_message();

			return true;
		}

		return false;
	}

	bool kcav::process_options_notification()
	{
		try
		{
			boost::program_options::notify(optionsMap);
		}
		catch (...)
		{
			handle_program_options_exceptions();

			return false;
		}

		return true;
	}

	bool kcav::load_image_file()
	{
		std::string imagePath = optionsMap["image-path"].as<std::string>();

		return generation.loadFromFile(imagePath);
	}

	void kcav::run_engine_loop()
	{
		cellular_automata_engine engine(std::move(cellularAutomaton), generation);
		sf::RenderWindow window(sf::VideoMode(generation.getSize().x, generation.getSize().y), "KCAV");
		sf::Time timer = sf::milliseconds(millisecondsPerGeneration);
		sf::Clock generationClock;
		sf::Time previousGenerationTime;

		while (window.isOpen())
		{
			sf::Event event;

			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();

					return;
				}
			}

			window.clear(sf::Color::Black);

			sf::Texture myTexture;

			myTexture.create(generation.getSize().x, generation.getSize().y);
			myTexture.update(generation);

			generation = engine.get_generation();

			sf::Sprite mySprite;

			mySprite.setTexture(myTexture);

			window.draw(mySprite);

			if (generationClock.getElapsedTime() - previousGenerationTime >= timer)
			{
				engine.update_generation();
				previousGenerationTime = generationClock.getElapsedTime();

			}

			window.display();
		}
	}

	void kcav::handle_program_options_exceptions() const
	{
		try
		{
			throw;
		}
		catch (boost::program_options::ambiguous_option&)
		{
			std::cerr << "Error: ambiguous option.\n";
		}
		catch (boost::program_options::unknown_option&)
		{
			std::cerr << "Error: unknown option.\n";
		}
		catch (boost::program_options::invalid_command_line_syntax&)
		{
			std::cerr << "Error: invalid command line syntax.\n";
		}
		catch (boost::program_options::multiple_occurrences& error)
		{
			std::cerr << "Error: multiple occurrences of the option " << error.get_option_name() << " are not allowed.\n";
		}
		catch (boost::program_options::multiple_values& error)
		{
			std::cerr << "Error: multiple values given to the option " << error.get_option_name() << " are not allowed.\n";
		}
		catch (boost::program_options::required_option& error)
		{
			std::cerr << "Error: missing required option " << error.get_option_name() << ".\n";
		}
		catch (boost::program_options::validation_error& error)
		{
			std::cerr << "Error: invalid value given to the option " << error.get_option_name() << ".\n";
		}
		catch (...)
		{
			std::cerr << "Error: exception caught while processing the program options.\n";
		}
	}

	void kcav::print_help_message() const
	{
		std::cout << "KCAV\n";
		std::cout << "Usage:\n";
		std::cout << "  kcav --help\n";
		std::cout << "  kcav --version\n";
		std::cout << "  kcav <cellular automaton identifier> <input file> [options]\n\n";

		std::cout << visibleOptions << "\n";
	}

	void kcav::print_version_message() const
	{
		std::cout << "KCAV\nVersion: 0.0.0\n";
	}

	void kcav::print_file_load_error_message() const
	{
		std::cerr << "Error: invalid file path.\n";
	}

	void kcav::print_invalid_identifier_error_message() const
	{
		std::cerr << "Error: invalid cellular automata identifier.\n";
	}

	void kcav::kcav::print_invalid_time_error_message() const
	{
		std::cerr << "Error: invalid time per generation.\n";
	}
}
