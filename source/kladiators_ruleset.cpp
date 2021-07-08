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
#include <vector>

#include <SFML/Graphics.hpp>

#include "kladiators_ruleset.hpp"

namespace kcav
{
	sf::Color kcav::kladiators_ruleset::get_state(sf::Color selfState, std::vector<sf::Color> neighbors)
	{
		sf::Color state = sf::Color::Black;
		int rgbSum = 0;

		for (int i = 0; i < 8; ++i)
		{
			int newSum = neighbors[i].r + neighbors[i].g + neighbors[i].b;

			if (newSum > rgbSum)
			{
				rgbSum = newSum;
				state = neighbors[i];
			}
		}

		return state;
	}
}
