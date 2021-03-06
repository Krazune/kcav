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
#ifndef WRAPPING_NEIGHBORS_SELECTOR_TEST_HPP
#define WRAPPING_NEIGHBORS_SELECTOR_TEST_HPP

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <gtest/gtest.h>

#include "../source/wrapping_neighbors_selector.hpp"

class WrappingNeighborsSelectorTest : public ::testing::Test
{
	protected:
	sf::Image singlePixelImage;	// Red.
	sf::Image rectangleImage;	// Red Green Blue, Cyan Magenta Yellow.

	std::vector<sf::Vector2<int>> vonNeumannNeighborhood;
	std::vector<sf::Vector2<int>> mooreNeighborhood;

	WrappingNeighborsSelectorTest()
	{
		singlePixelImage.create(1, 1, sf::Color::Red);

		rectangleImage.create(3, 2, sf::Color::Red);
		rectangleImage.setPixel(1, 0, sf::Color::Green);
		rectangleImage.setPixel(2, 0, sf::Color::Blue);
		rectangleImage.setPixel(0, 1, sf::Color::Cyan);
		rectangleImage.setPixel(1, 1, sf::Color::Magenta);
		rectangleImage.setPixel(2, 1, sf::Color::Yellow);

		vonNeumannNeighborhood = std::vector<sf::Vector2<int>>({
			{0, -1}, {1, 0}, {0, 1}, {-1, 0},
			{0, -2}, {2, 0}, {0, 2}, {-2, 0}
		});

		mooreNeighborhood = std::vector<sf::Vector2<int>>({
		   {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}
		});
	}
};

TEST_F(WrappingNeighborsSelectorTest, VonNeumannNeighborhoodSinglePixelTest)
{
	kcav::wrapping_neighbors_selector colorsSelector(vonNeumannNeighborhood);

	std::vector<sf::Color> colors = colorsSelector.get_neighbors(singlePixelImage, 0, 0);

	ASSERT_EQ(colors[0], sf::Color::Red);
	ASSERT_EQ(colors[1], sf::Color::Red);
	ASSERT_EQ(colors[2], sf::Color::Red);
	ASSERT_EQ(colors[3], sf::Color::Red);
	ASSERT_EQ(colors[4], sf::Color::Red);
	ASSERT_EQ(colors[5], sf::Color::Red);
	ASSERT_EQ(colors[6], sf::Color::Red);
	ASSERT_EQ(colors[7], sf::Color::Red);
}

TEST_F(WrappingNeighborsSelectorTest, MooreNeighborhoodTopLeftTest)
{
	kcav::wrapping_neighbors_selector colorsSelector(mooreNeighborhood);

	std::vector<sf::Color> colors = colorsSelector.get_neighbors(rectangleImage, 0, 0);

	ASSERT_EQ(colors[0], sf::Color::Cyan);
	ASSERT_EQ(colors[1], sf::Color::Magenta);
	ASSERT_EQ(colors[2], sf::Color::Green);
	ASSERT_EQ(colors[3], sf::Color::Magenta);
	ASSERT_EQ(colors[4], sf::Color::Cyan);
	ASSERT_EQ(colors[5], sf::Color::Yellow);
	ASSERT_EQ(colors[6], sf::Color::Blue);
	ASSERT_EQ(colors[7], sf::Color::Yellow);
}

TEST_F(WrappingNeighborsSelectorTest, MooreNeighborhoodBottomRightTest)
{
	kcav::wrapping_neighbors_selector colorsSelector(mooreNeighborhood);

	std::vector<sf::Color> colors = colorsSelector.get_neighbors(rectangleImage, 2, 1);

	ASSERT_EQ(colors[0], sf::Color::Blue);
	ASSERT_EQ(colors[1], sf::Color::Red);
	ASSERT_EQ(colors[2], sf::Color::Cyan);
	ASSERT_EQ(colors[3], sf::Color::Red);
	ASSERT_EQ(colors[4], sf::Color::Blue);
	ASSERT_EQ(colors[5], sf::Color::Green);
	ASSERT_EQ(colors[6], sf::Color::Magenta);
	ASSERT_EQ(colors[7], sf::Color::Green);
}

#endif
