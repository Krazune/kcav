#ifndef WRAPPING_NEIGHBORS_NEIGHBOR_COLOR_SELECTOR_TEST_HPP
#define WRAPPING_NEIGHBORS_NEIGHBOR_COLOR_SELECTOR_TEST_HPP

#include <vector>

#include <gtest/gtest.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "../source/wrapping_neighbors_neighbor_color_selector.hpp"

class WrappingNeighborsNeighborColorSelectorTest : public ::testing::Test
{
	protected:
	sf::Image singlePixelImage;	// Red.
	sf::Image rectangleImage;	// Red Green Blue, Cyan Magenta Yellow.

	std::vector<sf::Vector2<int>> vonNeumannNeighborhood;
	std::vector<sf::Vector2<int>> mooreNeighborhood;

	WrappingNeighborsNeighborColorSelectorTest()
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

TEST_F(WrappingNeighborsNeighborColorSelectorTest, VonNeumannNeighborhoodSinglePixelTest)
{
	kcav::wrapping_neighbors_neighbor_color_selector colorsSelector(vonNeumannNeighborhood);

	std::vector<sf::Color> colors = colorsSelector.get_colors(singlePixelImage, 0, 0);

	ASSERT_EQ(colors[0], sf::Color::Red);
	ASSERT_EQ(colors[1], sf::Color::Red);
	ASSERT_EQ(colors[2], sf::Color::Red);
	ASSERT_EQ(colors[3], sf::Color::Red);
	ASSERT_EQ(colors[4], sf::Color::Red);
	ASSERT_EQ(colors[5], sf::Color::Red);
	ASSERT_EQ(colors[6], sf::Color::Red);
	ASSERT_EQ(colors[7], sf::Color::Red);
}

TEST_F(WrappingNeighborsNeighborColorSelectorTest, MooreNeighborhoodTopLeftTest)
{
	kcav::wrapping_neighbors_neighbor_color_selector colorsSelector(mooreNeighborhood);

	std::vector<sf::Color> colors = colorsSelector.get_colors(rectangleImage, 0, 0);

	ASSERT_EQ(colors[0], sf::Color::Cyan);
	ASSERT_EQ(colors[1], sf::Color::Magenta);
	ASSERT_EQ(colors[2], sf::Color::Green);
	ASSERT_EQ(colors[3], sf::Color::Magenta);
	ASSERT_EQ(colors[4], sf::Color::Cyan);
	ASSERT_EQ(colors[5], sf::Color::Yellow);
	ASSERT_EQ(colors[6], sf::Color::Blue);
	ASSERT_EQ(colors[7], sf::Color::Yellow);
}

TEST_F(WrappingNeighborsNeighborColorSelectorTest, MooreNeighborhoodBottomRightTest)
{
	kcav::wrapping_neighbors_neighbor_color_selector colorsSelector(mooreNeighborhood);

	std::vector<sf::Color> colors = colorsSelector.get_colors(rectangleImage, 2, 1);

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
