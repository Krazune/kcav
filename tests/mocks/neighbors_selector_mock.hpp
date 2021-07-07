#ifndef NEIGHBORS_SELECTOR_MOCK_HPP
#define NEIGHBORS_SELECTOR_MOCK_HPP

#include <vector>

#include <SFML/Graphics.hpp>

#include <gmock/gmock.h>

#include "../source/neighbors_selector.hpp"

class neighbors_selector_mock : public kcav::neighbors_selector
{
	public:
	MOCK_METHOD(std::vector<sf::Color>, get_neighbors, (const sf::Image& image, unsigned int x, unsigned int y), (const, override));
};

#endif
