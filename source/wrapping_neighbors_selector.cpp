#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "wrapping_neighbors_selector.hpp"

namespace kcav
{
	wrapping_neighbors_selector::wrapping_neighbors_selector(const std::vector<sf::Vector2<int>> neighborOffsets) : offset_neighbors_selector(neighborOffsets) { }

	std::vector<sf::Color> wrapping_neighbors_selector::get_neighbors(const sf::Image &image, unsigned int x, unsigned int y) const
	{
		std::vector<sf::Color> neighborsColor;

		for (unsigned int i = 0; i < neighborOffsets.size(); ++i)
		{
			// Long long int is being used so that no bits are lost, and no ub happens, when the offset is negative, or bigger than the image size.
			long long int offsetX = static_cast<long long int>(x) + neighborOffsets[i].x;
			long long int offsetY = static_cast<long long int>(y) + neighborOffsets[i].y;

			long long int width = image.getSize().x;
			long long int height = image.getSize().y;

			unsigned int wrappedX = static_cast<unsigned int>((offsetX % width + width) % width);
			unsigned int wrappedY = static_cast<unsigned int>((offsetY % height + height) % height);

			neighborsColor.push_back(image.getPixel(wrappedX, wrappedY));
		}

		return neighborsColor;
	}
}
