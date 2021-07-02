#ifndef RULESET_MOCK_HPP
#define RULESET_MOCK_HPP

#include <vector>

#include <SFML/Graphics.hpp>

#include <gmock/gmock.h>

#include "../source/ruleset.hpp"

class ruleset_mock : public kcav::ruleset
{
	public:
	MOCK_METHOD(sf::Color, get_state, (sf::Color selfState, std::vector<sf::Color> neighbors), (override));
	MOCK_METHOD(bool, has_invalid_states, (const sf::Image& image), (override));
	MOCK_METHOD(sf::Image, convert_invalid_states, (const sf::Image& original), (override));
};

#endif
