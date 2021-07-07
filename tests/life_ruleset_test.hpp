#ifndef LIFE_RULESET_TEST_HPP
#define LIFE_RULESET_TEST_HPP

#include <vector>

#include <gtest/gtest.h>

#include <SFML/Graphics.hpp>

#include "../source/life_ruleset.hpp"

class LifeRulesetTest : public ::testing::Test
{
	protected:
	kcav::life_ruleset lifeRuleset;

	std::vector<sf::Color> zeroNeighbors = std::vector<sf::Color>(8, sf::Color::White);

	std::vector<sf::Color> oneNeighbors = std::vector<sf::Color>({
		sf::Color::Black, sf::Color::White, sf::Color::White, sf::Color::White,
		sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::White
	});

	std::vector<sf::Color> twoNeighbors = std::vector<sf::Color>({
		sf::Color::Black, sf::Color::Black, sf::Color::White, sf::Color::White,
		sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::White
	});

	std::vector<sf::Color> threeNeighbors = std::vector<sf::Color>({
		sf::Color::Black, sf::Color::Black, sf::Color::Black, sf::Color::White,
		sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::White
	});

	std::vector<sf::Color> fourNeighbors = std::vector<sf::Color>({
		sf::Color::Black, sf::Color::Black, sf::Color::Black, sf::Color::Black,
		sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::White
	});

	std::vector<sf::Color> fiveNeighbors = std::vector<sf::Color>({
		sf::Color::Black, sf::Color::Black, sf::Color::Black, sf::Color::Black,
		sf::Color::Black, sf::Color::White, sf::Color::White, sf::Color::White
	});

	std::vector<sf::Color> sixNeighbors = std::vector<sf::Color>({
		sf::Color::Black, sf::Color::Black, sf::Color::Black, sf::Color::Black,
		sf::Color::Black, sf::Color::Black, sf::Color::White, sf::Color::White
	});

	std::vector<sf::Color> sevenNeighbors = std::vector<sf::Color>({
		sf::Color::Black, sf::Color::Black, sf::Color::Black, sf::Color::Black,
		sf::Color::Black, sf::Color::Black, sf::Color::Black, sf::Color::White
	});

	std::vector<sf::Color> eightNeighbors = std::vector<sf::Color>(8, sf::Color::Black);

	sf::Image colorfulImage; // Red Green Blue, Cyan Magenta Yellow.
	sf::Image blackWhiteImage; // Black White, White Black.

	LifeRulesetTest()
	{
		colorfulImage.create(3, 2, sf::Color::Red);
		colorfulImage.setPixel(1, 0, sf::Color::Green);
		colorfulImage.setPixel(2, 0, sf::Color::Blue);
		colorfulImage.setPixel(0, 1, sf::Color::Cyan);
		colorfulImage.setPixel(1, 1, sf::Color::Magenta);
		colorfulImage.setPixel(2, 1, sf::Color::Yellow);

		blackWhiteImage.create(2, 2, sf::Color::White);
		blackWhiteImage.setPixel(0, 0, sf::Color::Black);
		blackWhiteImage.setPixel(1, 1, sf::Color::Black);
	}
};

TEST_F(LifeRulesetTest, WhiteStateZeroNeighborsTest)
{
	ASSERT_EQ(lifeRuleset.get_state(sf::Color::White, zeroNeighbors), sf::Color::White);
}

TEST_F(LifeRulesetTest, WhiteStateOneNeighborsTest)
{
	ASSERT_EQ(lifeRuleset.get_state(sf::Color::White, oneNeighbors), sf::Color::White);
}

TEST_F(LifeRulesetTest, WhiteStateTwoNeighborsTest)
{
	ASSERT_EQ(lifeRuleset.get_state(sf::Color::White, twoNeighbors), sf::Color::White);
}

TEST_F(LifeRulesetTest, WhiteStateThreeNeighborsTest)
{
	ASSERT_EQ(lifeRuleset.get_state(sf::Color::White, threeNeighbors), sf::Color::Black);
}

TEST_F(LifeRulesetTest, WhiteStateFourNeighborsTest)
{
	ASSERT_EQ(lifeRuleset.get_state(sf::Color::White, fourNeighbors), sf::Color::White);
}

TEST_F(LifeRulesetTest, WhiteStateFiveNeighborsTest)
{
	ASSERT_EQ(lifeRuleset.get_state(sf::Color::White, fiveNeighbors), sf::Color::White);
}

TEST_F(LifeRulesetTest, WhiteStateSixNeighborsTest)
{
	ASSERT_EQ(lifeRuleset.get_state(sf::Color::White, sixNeighbors), sf::Color::White);
}

TEST_F(LifeRulesetTest, WhiteStateSevenNeighborsTest)
{
	ASSERT_EQ(lifeRuleset.get_state(sf::Color::White, sevenNeighbors), sf::Color::White);
}

TEST_F(LifeRulesetTest, WhiteStateEightNeighborsTest)
{
	ASSERT_EQ(lifeRuleset.get_state(sf::Color::White, eightNeighbors), sf::Color::White);
}

TEST_F(LifeRulesetTest, BlackStateZeroNeighborsTest)
{
	ASSERT_EQ(lifeRuleset.get_state(sf::Color::Black, zeroNeighbors), sf::Color::White);
}

TEST_F(LifeRulesetTest, BlackStateOneNeighborsTest)
{
	ASSERT_EQ(lifeRuleset.get_state(sf::Color::Black, oneNeighbors), sf::Color::White);
}

TEST_F(LifeRulesetTest, BlackStateTwoNeighborsTest)
{
	ASSERT_EQ(lifeRuleset.get_state(sf::Color::Black, twoNeighbors), sf::Color::Black);
}

TEST_F(LifeRulesetTest, BlackStateThreeNeighborsTest)
{
	ASSERT_EQ(lifeRuleset.get_state(sf::Color::Black, threeNeighbors), sf::Color::Black);
}

TEST_F(LifeRulesetTest, BlackStateFourNeighborsTest)
{
	ASSERT_EQ(lifeRuleset.get_state(sf::Color::Black, fourNeighbors), sf::Color::White);
}

TEST_F(LifeRulesetTest, BlackStateFiveNeighborsTest)
{
	ASSERT_EQ(lifeRuleset.get_state(sf::Color::Black, fiveNeighbors), sf::Color::White);
}

TEST_F(LifeRulesetTest, BlackStateSixNeighborsTest)
{
	ASSERT_EQ(lifeRuleset.get_state(sf::Color::Black, sixNeighbors), sf::Color::White);
}

TEST_F(LifeRulesetTest, BlackStateSevenNeighborsTest)
{
	ASSERT_EQ(lifeRuleset.get_state(sf::Color::Black, sevenNeighbors), sf::Color::White);
}

TEST_F(LifeRulesetTest, BlackStateEightNeighborsTest)
{
	ASSERT_EQ(lifeRuleset.get_state(sf::Color::Black, eightNeighbors), sf::Color::White);
}

TEST_F(LifeRulesetTest, ColorfulImageInvalidStatesTest)
{
	ASSERT_TRUE(lifeRuleset.has_invalid_states(colorfulImage));
}

TEST_F(LifeRulesetTest, BlackWhiteImageInvalidStatesTest)
{
	ASSERT_FALSE(lifeRuleset.has_invalid_states(blackWhiteImage));
}

TEST_F(LifeRulesetTest, ColorfulImageConversionTest)
{
	sf::Image convertedImage = lifeRuleset.convert_invalid_states(colorfulImage);

	ASSERT_EQ(convertedImage.getPixel(0, 0), sf::Color::Black);
	ASSERT_EQ(convertedImage.getPixel(1, 0), sf::Color::White);
	ASSERT_EQ(convertedImage.getPixel(2, 0), sf::Color::Black);
	ASSERT_EQ(convertedImage.getPixel(0, 1), sf::Color::White);
	ASSERT_EQ(convertedImage.getPixel(1, 1), sf::Color::Black);
	ASSERT_EQ(convertedImage.getPixel(2, 1), sf::Color::White);
}

#endif
