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

#include "wrapping_neighbors_selector.hpp"

namespace kcav
{
	wrapping_neighbors_selector::wrapping_neighbors_selector(const std::vector<sf::Vector2<int>> neighborOffsets) :
		offset_neighbors_selector(neighborOffsets)
	{
	}

	std::vector<sf::Color> wrapping_neighbors_selector::get_neighbors(const sf::Image &image, unsigned int x, unsigned int y) const
	{
		std::vector<sf::Color> neighborsColor;

		for (unsigned int i = 0; i < neighborOffsets.size(); ++i)
		{
			// Long long int is being used so that no bits are lost, and no ub happens, when the offset is negative, or bigger than the image size.
			long long int offsetX = static_cast<long long int>(x) + neighborOffsets[i].x;
			long long int offsetY = static_cast<long long int>(y) + neighborOffsets[i].y;

			long long int width = image.getSize().x;
			long long int height = image.getSize().y;

			unsigned int wrappedX = static_cast<unsigned int>((offsetX % width + width) % width);
			unsigned int wrappedY = static_cast<unsigned int>((offsetY % height + height) % height);

			neighborsColor.push_back(image.getPixel(wrappedX, wrappedY));
		}

		return neighborsColor;
	}
}
