#ifndef NEIGHBOR_COLORS_SELECTOR_HPP
#define NEIGHBOR_COLORS_SELECTOR_HPP

#include <vector>

#include <SFML/Graphics.hpp>

namespace kcav
{
	class neighbor_colors_selector
	{
		public:
		virtual std::vector<sf::Color> get_colors(const sf::Image& image, unsigned int x, unsigned int y) const = 0;
	};
}

#endif
