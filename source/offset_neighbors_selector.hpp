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
#ifndef KCAV_OFFSET_NEIGHBORS_SELECTOR_HPP
#define KCAV_OFFSET_NEIGHBORS_SELECTOR_HPP

#include <vector>

#include <SFML/System.hpp>

#include "neighbors_selector.hpp"

namespace kcav
{
	class offset_neighbors_selector : public neighbors_selector
	{
		protected:
		const std::vector<sf::Vector2<int>> neighborOffsets;

		public:
		offset_neighbors_selector(const std::vector<sf::Vector2<int>> neighborOffsets);

		const std::vector<sf::Vector2<int>> get_offsets() const;
	};
}

#endif
