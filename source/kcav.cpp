#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>

#include <boost/program_options.hpp>

#include <SFML/Graphics.hpp>

#include "cellular_automata_engine.hpp"
#include "kcav.hpp"
#include "life_ruleset.hpp"

// TEMPORARY

#include "wrapping_neighbors_selector.hpp"
#include "cellular_automaton.hpp"
// TEMPORARY END

namespace kcav
{
	kcav::kcav() : options("Options")
	{
		setup_options();
	}

	int kcav::run(int argc, char* argv[])
	{
		boost::program_options::variables_map optionsMap;

		try
		{
			boost::program_options::parsed_options parsedOptions = boost::program_options::command_line_parser(argc, argv).options(options).positional(positionalOptions).run();

			boost::program_options::store(parsedOptions, optionsMap);
		}
		catch (...)
		{
			// Handle exceptions.
			std::cout << "options parsing error 1\n";

			return EXIT_FAILURE;
		}

		if (optionsMap.count("help") > 0)
		{
			std::cout << "usage information\n";

			return EXIT_SUCCESS;
		}

		if (optionsMap.count("version") > 0)
		{
			std::cout << "version information\n";

			return EXIT_SUCCESS;
		}

		try
		{
			boost::program_options::notify(optionsMap);

		} catch (...)
		{
			// Handle exceptions.
			std::cout << "options parsing error 2\n";

			return EXIT_FAILURE;
		}

		std::string rulesetIdentifier = optionsMap["ruleset"].as<std::string>();
		std::string imagePath = optionsMap["image-path"].as<std::string>();
		int millisecondsPerGeneration = optionsMap["time"].as<int>();

		sf::Image inputImage;

		// Handle file load error.
		inputImage.loadFromFile(imagePath);

		std::unique_ptr<ruleset> ruleset;
		std::unique_ptr<neighbors_selector> neighborsSelector;

		if (rulesetIdentifier == "life")
		{
			ruleset = std::make_unique<life_ruleset>();
			neighborsSelector = std::make_unique<wrapping_neighbors_selector>(std::vector<sf::Vector2<int>>({
																											   {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}
																											}));
		}
		else
		{
			std::cout << "unknown ruleset\n";

			return EXIT_FAILURE;
		}

		if (millisecondsPerGeneration < 0)
		{
			std::cout << "invalid generation time\n";

			return EXIT_FAILURE;
		}

		inputImage = ruleset->convert_invalid_states(inputImage);

		auto cellularAutomaton = std::make_unique<cellular_automaton>(std::move(ruleset), std::move(neighborsSelector));

		cellular_automata_engine engine(std::move(cellularAutomaton), inputImage);

		sf::RenderWindow window(sf::VideoMode(inputImage.getSize().x, inputImage.getSize().y), "KCAV");

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
				}
			}

			window.clear(sf::Color::Black);

			sf::Texture myTexture;

			myTexture.create(inputImage.getSize().x, inputImage.getSize().y);
			myTexture.update(inputImage);

			inputImage = engine.get_generation();

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

		return EXIT_SUCCESS;
	}

	void kcav::setup_options()
	{
		boost::program_options::options_description hiddenOptions = create_hidden_options();
		boost::program_options::options_description visibleOptions = create_visible_options();

		options.add(visibleOptions).add(hiddenOptions);

		positionalOptions = create_positional_options();
	}

	boost::program_options::options_description kcav::create_hidden_options() const
	{
		boost::program_options::options_description hiddenOptions("Hidden options");

		hiddenOptions.add_options()
			("help", "print help information")
			("version", "print version information")
			("ruleset", boost::program_options::value<std::string>()->required(), "cellular automaton ruleset identifier")
			("image-path", boost::program_options::value<std::string>()->required(), "input image path");

		return hiddenOptions;
	}

	boost::program_options::options_description kcav::create_visible_options() const
	{
		boost::program_options::options_description visibleOptions("Options");

		visibleOptions.add_options()
			("time,t", boost::program_options::value<int>()->default_value(100), "amount of miliseconds between each generation");

		return visibleOptions;
	}

	boost::program_options::positional_options_description kcav::create_positional_options() const
	{
		boost::program_options::positional_options_description positionalOptions;

		positionalOptions.add("ruleset", 1).add("image-path", 1);

		return positionalOptions;
	}
}
