#include "constant_neighbors_neighbor_colors_selector.hpp"
#include "neighbor_colors_selector.hpp"

namespace kcav
{
	constant_neighbors_neighbor_colors_selector::constant_neighbors_neighbor_colors_selector(const std::vector<sf::Vector2<int>> neighborOffsets) : neighbor_colors_selector(), neighborOffsets (neighborOffsets) { }

	const std::vector<sf::Vector2<int> > constant_neighbors_neighbor_colors_selector::get_neighbor_offsets() const
	{
		return neighborOffsets;
	}
}
