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
