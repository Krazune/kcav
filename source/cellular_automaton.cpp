#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "cellular_automaton.hpp"
#include "neighbors_selector.hpp"
#include "ruleset.hpp"

namespace kcav
{
	cellular_automaton::cellular_automaton(std::unique_ptr<ruleset> ruleset, std::unique_ptr<neighbors_selector> neighborsSelector) : automatonRuleset(std::move(ruleset)), neighborsSelector(std::move(neighborsSelector)) { }

	sf::Image cellular_automaton::get_next_generation(const sf::Image& currentGeneration)
	{
		unsigned int width = currentGeneration.getSize().x;
		unsigned int height = currentGeneration.getSize().y;

		sf::Image nextGeneration;

		nextGeneration.create(width, height, sf::Color::Transparent);

		for (unsigned int x = 0; x < width; ++x)
		{
			for (unsigned int y = 0; y < height; ++y)
			{
				std::vector<sf::Color> neighbors = neighborsSelector->get_neighbors(currentGeneration, x, y);
				sf::Color selfState = currentGeneration.getPixel(x, y);
				sf::Color nextState = automatonRuleset->get_state(selfState, neighbors);

				nextGeneration.setPixel(x, y, nextState);
			}
		}

		return nextGeneration;
	}
}
