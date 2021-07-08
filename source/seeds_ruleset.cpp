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

#include <SFML/Graphics.hpp>

#include "seeds_ruleset.hpp"

namespace kcav
{
	sf::Color seeds_ruleset::get_state(sf::Color selfState, std::vector<sf::Color> neighbors)
	{
		int neighborCount = 0;

		for (int i = 0; i < 8; ++i)
		{
			if (neighbors[i] == sf::Color::Black)
			{
				++neighborCount;
			}
		}

		if (neighborCount == 2)
		{
			return sf::Color::Black;
		}

		return sf::Color::White;
	}

	bool seeds_ruleset::has_invalid_states(const sf::Image& image)
	{
		for (unsigned int x = 0; x < image.getSize().x; ++x)
		{
			for (unsigned int y = 0; y < image.getSize().y; ++y)
			{
				sf::Color state = image.getPixel(x, y);

				if (state != sf::Color::Black && state != sf::Color::White)
				{
					return true;
				}
			}
		}

		return false;
	}

	sf::Image seeds_ruleset::convert_invalid_states(const sf::Image& original)
	{
		sf::Image validImage;

		unsigned int width = original.getSize().x;
		unsigned int height = original.getSize().y;

		validImage.create(width, height, sf::Color::White);

		for (unsigned int x = 0; x < width; ++x)
		{
			for (unsigned int y = 0; y < height; ++y)
			{
				sf::Color state = original.getPixel(x, y);
				float r = static_cast<float>(state.r) / 255;
				float g = static_cast<float>(state.g) / 255;
				float b = static_cast<float>(state.b) / 255;
				float luminance = 0.2126 * r + 0.7152 * g + 0.0722 * b; // This formula is not very accurate, but it's good enough for this.

				if (luminance < 0.5)
				{
					validImage.setPixel(x, y, sf::Color::Black);
				}
			}
		}

		return validImage;
	}
}
