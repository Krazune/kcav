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
