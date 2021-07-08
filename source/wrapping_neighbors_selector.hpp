#ifndef WRAPPING_NEIGHBORS_SELECTOR_HPP
#define WRAPPING_NEIGHBORS_SELECTOR_HPP

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "offset_neighbors_selector.hpp"

namespace kcav
{
	class wrapping_neighbors_selector : public offset_neighbors_selector
	{
		public:
		wrapping_neighbors_selector(const std::vector<sf::Vector2<int>> neighborOffsets);

		std::vector<sf::Color> get_neighbors(const sf::Image& image, unsigned int x, unsigned int y) const override;
	};
}

#endif
