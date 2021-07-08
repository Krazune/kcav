#include <vector>

#include <SFML/System.hpp>

#include "neighbors_selector.hpp"
#include "offset_neighbors_selector.hpp"

namespace kcav
{
	offset_neighbors_selector::offset_neighbors_selector(const std::vector<sf::Vector2<int>> neighborOffsets) :
		neighbors_selector(),
		neighborOffsets (neighborOffsets)
	{
	}

	const std::vector<sf::Vector2<int> > offset_neighbors_selector::get_offsets() const
	{
		return neighborOffsets;
	}
}
