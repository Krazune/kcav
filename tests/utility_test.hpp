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
#ifndef KCAV_UTILITY_TEST_HPP
#define KCAV_UTILITY_TEST_HPP

#include <vector>

#include <SFML/Graphics.hpp>

#include <gtest/gtest.h>

#include "../source/utility.hpp"

TEST(UtilityTest, ClosestRgbColorTest)
{
	std::vector<sf::Color> colors;

	colors.push_back(sf::Color::Red);
	colors.push_back(sf::Color::Green);
	colors.push_back(sf::Color::Blue);

	EXPECT_EQ(kcav::get_closest_color(sf::Color::Red, colors), sf::Color::Red);
	EXPECT_EQ(kcav::get_closest_color(sf::Color::Green, colors), sf::Color::Green);
	EXPECT_EQ(kcav::get_closest_color(sf::Color::Blue, colors), sf::Color::Blue);

	EXPECT_EQ(kcav::get_closest_color(sf::Color(100, 100, 100), colors), sf::Color::Blue);
}

TEST(UtilityTest, ClosestBlackWhiteColorTest)
{
	std::vector<sf::Color> colors;

	colors.push_back(sf::Color::Black);
	colors.push_back(sf::Color::White);

	EXPECT_EQ(kcav::get_closest_color(sf::Color::Black, colors), sf::Color::Black);
	EXPECT_EQ(kcav::get_closest_color(sf::Color::White, colors), sf::Color::White);

	EXPECT_EQ(kcav::get_closest_color(sf::Color::Red, colors), sf::Color::Black);
	EXPECT_EQ(kcav::get_closest_color(sf::Color::Green, colors), sf::Color::Black);
	EXPECT_EQ(kcav::get_closest_color(sf::Color::Yellow, colors), sf::Color::White);
}

TEST(UtilityTest, ColorDifferenceTest)
{
	EXPECT_EQ(kcav::get_color_difference(sf::Color::Red, sf::Color::Red), 0);
	EXPECT_EQ(kcav::get_color_difference(sf::Color::Green, sf::Color::Green), 0);
	EXPECT_EQ(kcav::get_color_difference(sf::Color::Blue, sf::Color::Blue), 0);
	EXPECT_EQ(kcav::get_color_difference(sf::Color::Black, sf::Color::Black), 0);
	EXPECT_EQ(kcav::get_color_difference(sf::Color::White, sf::Color::White), 0);

	EXPECT_EQ(kcav::get_color_difference(sf::Color::Red, sf::Color::Green), 255 * 255 * 2);
	EXPECT_EQ(kcav::get_color_difference(sf::Color::Red, sf::Color::Blue), 255 * 255 * 2);
	EXPECT_EQ(kcav::get_color_difference(sf::Color::Green, sf::Color::Blue), 255 * 255 * 2);

	EXPECT_EQ(kcav::get_color_difference(sf::Color::Black, sf::Color(1, 2, 3)), 1 + 2 * 2 + 3 * 3);
}

#endif
