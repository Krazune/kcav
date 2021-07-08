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
#ifndef CELLULAR_AUTOMATON_TEST_HPP
#define CELLULAR_AUTOMATON_TEST_HPP

#include <memory>
#include <utility>

#include <SFML/Graphics.hpp>

#include <gtest/gtest.h>

#include "../source/cellular_automaton.hpp"

#include "mocks/neighbors_selector_mock.hpp"
#include "mocks/ruleset_mock.hpp"

class CellularAutomatonTest : public ::testing::Test
{
	protected:
	std::unique_ptr<ruleset_mock> rulesetMock = std::make_unique<ruleset_mock>();
	std::unique_ptr<neighbors_selector_mock> neighborsSelectorMock = std::make_unique<neighbors_selector_mock>();

	sf::Image colorfulImage;	// Red Green Blue, Cyan Magenta Yellow.
	sf::Image redImage;			// Red Red Red, Red Red Red.

	CellularAutomatonTest()
	{
		colorfulImage.create(3, 2, sf::Color::Red);
		colorfulImage.setPixel(1, 0, sf::Color::Green);
		colorfulImage.setPixel(2, 0, sf::Color::Blue);
		colorfulImage.setPixel(0, 1, sf::Color::Cyan);
		colorfulImage.setPixel(1, 1, sf::Color::Magenta);
		colorfulImage.setPixel(2, 1, sf::Color::Yellow);

		redImage.create(3, 2, sf::Color::Red);
	}
};

TEST_F(CellularAutomatonTest, GetNextGenerationTest)
{
	EXPECT_CALL(*rulesetMock, get_state(::testing::_, ::testing::_)).Times(6).WillRepeatedly(::testing::Return(sf::Color::Red));
	EXPECT_CALL(*neighborsSelectorMock, get_neighbors(::testing::_, ::testing::_, ::testing::_)).Times(6).WillRepeatedly(::testing::Return(std::vector<sf::Color>(8, sf::Color::Black)));

	kcav::cellular_automaton cellularAutomaton(std::move(rulesetMock), std::move(neighborsSelectorMock));

	const sf::Image nextGeneration = cellularAutomaton.get_next_gen(colorfulImage);

	ASSERT_EQ(nextGeneration.getPixel(0, 0), sf::Color::Red);
	ASSERT_EQ(nextGeneration.getPixel(1, 0), sf::Color::Red);
	ASSERT_EQ(nextGeneration.getPixel(2, 0), sf::Color::Red);
	ASSERT_EQ(nextGeneration.getPixel(0, 1), sf::Color::Red);
	ASSERT_EQ(nextGeneration.getPixel(1, 1), sf::Color::Red);
	ASSERT_EQ(nextGeneration.getPixel(2, 1), sf::Color::Red);
}

TEST_F(CellularAutomatonTest, ConvertInvalidStatesTest)
{
	EXPECT_CALL(*rulesetMock, convert_invalid_states(::testing::_)).WillOnce(::testing::Return(redImage));

	kcav::cellular_automaton cellularAutomaton(std::move(rulesetMock), std::move(neighborsSelectorMock));

	const sf::Image validGeneration = cellularAutomaton.convert_invalid_states(colorfulImage);

	ASSERT_EQ(validGeneration.getPixel(0, 0), sf::Color::Red);
	ASSERT_EQ(validGeneration.getPixel(1, 0), sf::Color::Red);
	ASSERT_EQ(validGeneration.getPixel(2, 0), sf::Color::Red);
	ASSERT_EQ(validGeneration.getPixel(0, 1), sf::Color::Red);
	ASSERT_EQ(validGeneration.getPixel(1, 1), sf::Color::Red);
	ASSERT_EQ(validGeneration.getPixel(2, 1), sf::Color::Red);
}

#endif
