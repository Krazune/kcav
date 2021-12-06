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
#include <map>
#include <vector>

#include <SFML/Graphics.hpp>

#include "pilots_ruleset.hpp"
#include "utility.hpp"

namespace kcav
{
	sf::Color pilots_ruleset::get_state(sf::Color selfState, std::vector<sf::Color> neighbors)
	{
		if (selfState == sf::Color::Black)
		{
			return sf::Color::Black;
		}

		bool redComing = neighbors[3] == sf::Color::Red;
		bool greenComing = neighbors[1] == sf::Color::Green;
		bool blueComing = neighbors[0] == sf::Color::Blue;
		bool yellownComing = neighbors[2] == sf::Color::Yellow;

		int comingCount = 0;

		if (redComing)
		{
			++comingCount;
		}

		if (greenComing)
		{
			++comingCount;
		}

		if (blueComing)
		{
			++comingCount;
		}

		if (yellownComing)
		{
			++comingCount;
		}

		if (comingCount == 1)
		{
			if (redComing)
			{
				return sf::Color::Red;
			}

			if (greenComing)
			{
				return sf::Color::Green;
			}

			if (blueComing)
			{
				return sf::Color::Blue;
			}

			if (yellownComing)
			{
				return sf::Color::Yellow;
			}
		}
		else if (comingCount > 1)
		{
			return sf::Color::Black;
		}

		return sf::Color::White;
	}

	bool pilots_ruleset::has_invalid_states(const sf::Image& image)
	{
		unsigned int width = image.getSize().x;
		unsigned int height = image.getSize().y;

		for (unsigned int x = 0; x < width; ++x)
		{
			for (unsigned int y = 0; y < height; ++y)
			{
				sf::Color state = image.getPixel(x, y);

				if (state != sf::Color::Black &&
					state != sf::Color::White &&
					state != sf::Color::Red &&
					state != sf::Color::Green &&
					state != sf::Color::Blue &&
					state != sf::Color::Yellow)
				{
					return false;
				}
			}
		}

		return true;
	}

	sf::Image pilots_ruleset::convert_invalid_states(const sf::Image& original)
	{
		sf::Image validImage;

		unsigned int width = original.getSize().x;
		unsigned int height = original.getSize().y;

		validImage.create(width, height, sf::Color::White);

		for (unsigned int x = 0; x < width; ++x)
		{
			for (unsigned int y = 0; y < height; ++y)
			{
				validImage.setPixel(x, y, get_closest_color(original.getPixel(x, y), validColors));
			}
		}

		return validImage;
	}
}
