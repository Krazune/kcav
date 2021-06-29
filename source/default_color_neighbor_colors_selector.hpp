#ifndef DEFAULT_COLOR_NEIGHBOR_COLORS_SELECTOR_HPP
#define DEFAULT_COLOR_NEIGHBOR_COLORS_SELECTOR_HPP

#include <vector>

#include <SFML/Graphics.hpp>

#include "constant_neighbors_neighbor_colors_selector.hpp"

namespace kcav
{
	class default_color_neighbor_colors_selector : public constant_neighbors_neighbor_colors_selector
	{
		const sf::Color defaultColor;

		public:
		default_color_neighbor_colors_selector(const std::vector<sf::Vector2<int>> neighborOffsets, const sf::Color defaultColor);

		std::vector<sf::Color> get_colors(const sf::Image& image, unsigned int x, unsigned int y) const override;
	};
}

#endif
