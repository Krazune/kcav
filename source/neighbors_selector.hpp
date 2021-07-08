#ifndef KCAV_NEIGHBORS_SELECTOR_HPP
#define KCAV_NEIGHBORS_SELECTOR_HPP

#include <vector>

#include <SFML/Graphics.hpp>

namespace kcav
{
	class neighbors_selector
	{
		public:
		virtual ~neighbors_selector() = default;
		virtual std::vector<sf::Color> get_neighbors(const sf::Image& image, unsigned int x, unsigned int y) const = 0;
	};
}

#endif
