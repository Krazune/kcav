#include <memory>
#include <utility>
#include <vector>

#include <SFML/Graphics.hpp>

#include "cellular_automaton.hpp"
#include "neighbors_selector.hpp"
#include "ruleset.hpp"

namespace kcav
{
	cellular_automaton::cellular_automaton(std::unique_ptr<ruleset> ruleset, std::unique_ptr<neighbors_selector> neighborsSelector) :
		automatonRuleset(std::move(ruleset)),
		neighborsSelector(std::move(neighborsSelector))
	{
	}

	sf::Image cellular_automaton::get_next_gen(const sf::Image& currentGen)
	{
		unsigned int width = currentGen.getSize().x;
		unsigned int height = currentGen.getSize().y;

		sf::Image nextGeneration;

		nextGeneration.create(width, height, sf::Color::Transparent);

		for (unsigned int x = 0; x < width; ++x)
		{
			for (unsigned int y = 0; y < height; ++y)
			{
				std::vector<sf::Color> neighbors = neighborsSelector->get_neighbors(currentGen, x, y);
				sf::Color selfState = currentGen.getPixel(x, y);
				sf::Color nextState = automatonRuleset->get_state(selfState, neighbors);

				nextGeneration.setPixel(x, y, nextState);
			}
		}

		return nextGeneration;
	}

	sf::Image cellular_automaton::convert_invalid_states(const sf::Image& original)
	{
		return automatonRuleset->convert_invalid_states(original);
	}
}
