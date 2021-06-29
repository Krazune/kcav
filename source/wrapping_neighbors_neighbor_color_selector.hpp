#ifndef WRAPPING_NEIGHBORS_NEIGHBOR_COLOR_SELECTOR_HPP
#define WRAPPING_NEIGHBORS_NEIGHBOR_COLOR_SELECTOR_HPP

#include <vector>

#include <SFML/Graphics.hpp>

#include "constant_neighbors_neighbor_colors_selector.hpp"

namespace kcav
{
	class wrapping_neighbors_neighbor_color_selector : public constant_neighbors_neighbor_colors_selector
	{
		public:
		wrapping_neighbors_neighbor_color_selector(const std::vector<sf::Vector2<int>> neighborOffsets);

		std::vector<sf::Color> get_colors(const sf::Image& image, unsigned int x, unsigned int y) const override;
	};
}

#endif
