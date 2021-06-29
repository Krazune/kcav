#ifndef OFFSET_NEIGHBORS_SELECTOR_HPP
#define OFFSET_NEIGHBORS_SELECTOR_HPP

#include <vector>

#include <SFML/System.hpp>

#include "neighbors_selector.hpp"

namespace kcav
{
	class offset_neighbors_selector : public neighbors_selector
	{
		protected:
		const std::vector<sf::Vector2<int>> neighborOffsets;

		public:
		offset_neighbors_selector(const std::vector<sf::Vector2<int>> neighborOffsets);

		const std::vector<sf::Vector2<int>> get_offsets() const;
	};
}

#endif
