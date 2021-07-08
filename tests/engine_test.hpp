#ifndef ENGINE_TEST_HPP
#define ENGINE_TEST_HPP

#include <memory>
#include <utility>

#include <SFML/Graphics.hpp>

#include <gtest/gtest.h>

#include "../source/engine.hpp"
#include "../source/cellular_automaton.hpp"

#include "mocks/neighbors_selector_mock.hpp"
#include "mocks/ruleset_mock.hpp"

class CellularAutomatonEngineTest : public ::testing::Test
{
	protected:
	std::unique_ptr<ruleset_mock> ruleset = std::make_unique<ruleset_mock>();
	std::unique_ptr<neighbors_selector_mock> neighborsSelector = std::make_unique<neighbors_selector_mock>();

	sf::Image colorfulImage;	// Red Green Blue, Cyan Magenta Yellow.
	sf::Image redImage;			// Red Red Red, Red Red Red.

	CellularAutomatonEngineTest()
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

TEST_F(CellularAutomatonEngineTest, GenerateAndGetGenerationTest)
{
	EXPECT_CALL(*ruleset, convert_invalid_states(::testing::_)).WillOnce(::testing::Return(redImage));
	EXPECT_CALL(*ruleset, get_state(::testing::_, ::testing::_)).WillRepeatedly(::testing::Return(sf::Color::Red));

	std::unique_ptr<kcav::cellular_automaton> cellularAutomaton = std::make_unique<kcav::cellular_automaton>(std::move(ruleset), std::move(neighborsSelector));
	kcav::engine cellularAutomataEngine(std::move(cellularAutomaton), colorfulImage);

	cellularAutomataEngine.update_gen();

	sf::Image generation = cellularAutomataEngine.get_gen();

	ASSERT_EQ(generation.getPixel(0, 0), sf::Color::Red);
	ASSERT_EQ(generation.getPixel(1, 0), sf::Color::Red);
	ASSERT_EQ(generation.getPixel(2, 0), sf::Color::Red);
	ASSERT_EQ(generation.getPixel(0, 1), sf::Color::Red);
	ASSERT_EQ(generation.getPixel(1, 1), sf::Color::Red);
	ASSERT_EQ(generation.getPixel(2, 1), sf::Color::Red);
}

#endif
