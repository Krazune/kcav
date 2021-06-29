#ifndef CONSTANT_NEIGHBORS_NEIGHBOR_COLORS_SELECTOR_HPP
#define CONSTANT_NEIGHBORS_NEIGHBOR_COLORS_SELECTOR_HPP

#include <vector>

#include <SFML/System.hpp>

#include "neighbor_colors_selector.hpp"

namespace kcav
{
	class constant_neighbors_neighbor_colors_selector : public neighbor_colors_selector
	{
		protected:
		const std::vector<sf::Vector2<int>> neighborOffsets;

		public:
		constant_neighbors_neighbor_colors_selector(const std::vector<sf::Vector2<int>> neighborOffsets);

		const std::vector<sf::Vector2<int>> get_neighbor_offsets() const;
	};
}

#endif
