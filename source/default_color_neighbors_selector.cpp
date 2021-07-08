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
#include <SFML/System.hpp>

#include "default_color_neighbors_selector.hpp"

namespace kcav
{
	default_color_neighbors_selector::default_color_neighbors_selector(const std::vector<sf::Vector2<int>> neighborOffsets, const sf::Color defaultColor) :
		offset_neighbors_selector(neighborOffsets), defaultColor (defaultColor)
	{
	}

	std::vector<sf::Color> default_color_neighbors_selector::get_neighbors(const sf::Image &image, unsigned int x, unsigned int y) const
	{
		std::vector<sf::Color> neighborColors;

		for (unsigned int i = 0; i < neighborOffsets.size(); ++i)
		{
			// Long long int is being used so that no bits are lost, and no ub happens, when the offset is negative, or bigger than the image size.
			long long int offsetX = static_cast<long long int>(x) + neighborOffsets[i].x;
			long long int offsetY = static_cast<long long int>(y) + neighborOffsets[i].y;

			if (offsetY < 0 || offsetX < 0 || offsetX >= static_cast<long long int>(image.getSize().x) || offsetY >= static_cast<long long int>(image.getSize().y))
			{
				neighborColors.push_back(defaultColor);

				continue;
			}

			neighborColors.push_back(image.getPixel(static_cast<unsigned int>(offsetX), static_cast<unsigned int>(offsetY)));
		}

		return neighborColors;
	}
}
