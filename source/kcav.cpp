/*
	MIT License

	Copyright (c) 2021 Miguel Sousa

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <boost/program_options.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "brians_brain_ruleset.hpp"
#include "cellular_automaton.hpp"
#include "engine.hpp"
#include "kcav.hpp"
#include "kladiators_ruleset.hpp"
#include "lfod_ruleset.hpp"
#include "life_ruleset.hpp"
#include "pilots_ruleset.hpp"
#include "seeds_ruleset.hpp"
#include "sfml_err_redirector.hpp"
#include "wrapping_neighbors_selector.hpp"

namespace po = boost::program_options;

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

	std::vector<sf::Vector2<int>> kcav::immediateNeighbors(
		{
			{0, -1}, {1, 0}, {0, 1}, {-1, 0}
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

		if (!setup_first_frame_time())
		{
			print_invalid_first_frame_time_error_message();

			return EXIT_FAILURE;
		}

		if (!setup_scale())
		{
			print_invalid_scale_error_message();

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
			("ruleset", po::value<std::string>()->required(), "cellular automaton ruleset identifier")
			("image-path", po::value<std::string>()->required(), "input image path");
	}

	void kcav::setup_visible_options()
	{
		visibleOptions.add_options()
			("time,t", po::value<int>()->default_value(100), "amount of miliseconds between each generation")
			("first-frame-time", po::value<int>()->default_value(1000), "amount of miliseconds for the first frame")
			("scale,s", po::value<float>()->default_value(1), "window scale");
	}

	void kcav::setup_positional_options()
	{
		positionalOptions.add("ruleset", 1).add("image-path", 1);
	}

	void kcav::setup_options_map(int argc, char* argv[])
	{
		po::parsed_options parsedOptions = po::command_line_parser(argc, argv).options(options).positional(positionalOptions).run();

		po::store(parsedOptions, optionsMap);
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
		else if (rulesetIdentifier == "seeds")
		{
			ruleset = std::make_unique<seeds_ruleset>();
			neighborsSelector = std::make_unique<wrapping_neighbors_selector>(mooreNeighbors);
		}
		else if (rulesetIdentifier == "brians-brain")
		{
			ruleset = std::make_unique<brians_brain_ruleset>();
			neighborsSelector = std::make_unique<wrapping_neighbors_selector>(mooreNeighbors);
		}
		else if (rulesetIdentifier == "kladiators")
		{
			ruleset = std::make_unique<kladiators_ruleset>();
			neighborsSelector = std::make_unique<wrapping_neighbors_selector>(vonNeumannNeighbors);
		}
		else if (rulesetIdentifier == "lfod")
		{
			ruleset = std::make_unique<lfod_ruleset>();
			neighborsSelector = std::make_unique<wrapping_neighbors_selector>(mooreNeighbors);
		}
		else if (rulesetIdentifier == "pilots")
		{
			ruleset = std::make_unique<pilots_ruleset>();
			neighborsSelector = std::make_unique<wrapping_neighbors_selector>(immediateNeighbors);
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

	bool kcav::setup_first_frame_time()
	{
		int time = optionsMap["first-frame-time"].as<int>();

		if (time < 0)
		{
			return false;
		}

		firstFrameMilliseconds = time;

		return true;
	}

	bool kcav::setup_scale()
	{
		int scale = optionsMap["scale"].as<float>();

		if (scale < 1)
		{
			return false;
		}

		this->scale = scale;

		return true;
	}

	bool kcav::process_option_storage(int argc, char* argv[])
	{
		try
		{
			setup_options_map(argc, argv);
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
			po::notify(optionsMap);
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

		return gen.loadFromFile(imagePath);
	}

	void kcav::run_engine_loop()
	{
		engine engine(std::move(cellularAutomaton), gen);

		gen = engine.get_gen();

		sf::RenderWindow window(sf::VideoMode(gen.getSize().x, gen.getSize().y), "KCAV");
		sf::Time timer = sf::milliseconds(millisecondsPerGeneration);
		sf::Clock generationClock;
		sf::Time previousGenerationTime = sf::milliseconds(firstFrameMilliseconds);

		window.setSize(sf::Vector2u(gen.getSize().x * scale, gen.getSize().y * scale));

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

			window.clear(sf::Color::White);

			sf::Texture myTexture;

			myTexture.create(gen.getSize().x, gen.getSize().y);
			myTexture.update(gen);

			gen = engine.get_gen();

			sf::Sprite mySprite;

			mySprite.setTexture(myTexture);

			window.draw(mySprite);

			if (generationClock.getElapsedTime() - previousGenerationTime >= timer)
			{
				engine.update_gen();
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
		catch (po::ambiguous_option&)
		{
			std::cerr << "Error: ambiguous option.\n";
		}
		catch (po::unknown_option&)
		{
			std::cerr << "Error: unknown option.\n";
		}
		catch (po::invalid_command_line_syntax&)
		{
			std::cerr << "Error: invalid command line syntax.\n";
		}
		catch (po::multiple_occurrences& error)
		{
			std::cerr << "Error: multiple occurrences of the option " << error.get_option_name() << " are not allowed.\n";
		}
		catch (po::multiple_values& error)
		{
			std::cerr << "Error: multiple values given to the option " << error.get_option_name() << " are not allowed.\n";
		}
		catch (po::required_option& error)
		{
			std::cerr << "Error: missing required option " << error.get_option_name() << ".\n";
		}
		catch (po::validation_error& error)
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
		std::cout << "KCAV\nVersion: 2021.12.1\n";
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

	void kcav::print_invalid_first_frame_time_error_message() const
	{
		std::cerr << "Error: invalid first frame time.\n";
	}

	void kcav::print_invalid_scale_error_message() const
	{
		std::cerr << "Error: invalid scale.\n";
	}
}
