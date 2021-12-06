#ifndef KCAV_UTILITY_TEST_HPP
#define KCAV_UTILITY_TEST_HPP

#include <SFML/Graphics.hpp>

#include <gtest/gtest.h>

#include "../source/utility.hpp"

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
