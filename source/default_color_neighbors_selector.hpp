#ifndef KCAV_DEFAULT_COLOR_NEIGHBORS_SELECTOR_HPP
#define KCAV_DEFAULT_COLOR_NEIGHBORS_SELECTOR_HPP

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "offset_neighbors_selector.hpp"

namespace kcav
{
	class default_color_neighbors_selector : public offset_neighbors_selector
	{
		const sf::Color defaultColor;

		public:
		default_color_neighbors_selector(const std::vector<sf::Vector2<int>> neighborOffsets, const sf::Color defaultColor);

		std::vector<sf::Color> get_neighbors(const sf::Image& image, unsigned int x, unsigned int y) const override;
	};
}

#endif
