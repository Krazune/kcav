#include <vector>

#include <SFML/Graphics.hpp>

#include "lfod_ruleset.hpp"

namespace kcav
{
	sf::Color lfod_ruleset::get_state(sf::Color selfState, std::vector<sf::Color> neighbors)
	{
		int neighborCount = 0;

		if (selfState == sf::Color::Black)
		{
			neighborCount = 1;
		}

		for (int i = 0; i < 8; ++i)
		{
			if (neighbors[i] == sf::Color::Black)
			{
				++neighborCount;
			}
		}

		if (neighborCount == 0)
		{
			return selfState;
		}

		if (selfState == sf::Color::White && neighborCount == 2)
		{
			return sf::Color::Black;
		}

		return sf::Color::White;
	}

	bool lfod_ruleset::has_invalid_states(const sf::Image& image)
	{
		for (unsigned int x = 0; x < image.getSize().x; ++x)
		{
			for (unsigned int y = 0; y < image.getSize().y; ++y)
			{
				sf::Color state = image.getPixel(x, y);

				if (state != sf::Color::Black && state != sf::Color::White)
				{
					return true;
				}
			}
		}

		return false;
	}

	sf::Image lfod_ruleset::convert_invalid_states(const sf::Image& original)
	{
		sf::Image validImage;

		unsigned int width = original.getSize().x;
		unsigned int height = original.getSize().y;

		validImage.create(width, height, sf::Color::White);

		for (unsigned int x = 0; x < width; ++x)
		{
			for (unsigned int y = 0; y < height; ++y)
			{
				sf::Color state = original.getPixel(x, y);
				float r = static_cast<float>(state.r) / 255;
				float g = static_cast<float>(state.g) / 255;
				float b = static_cast<float>(state.b) / 255;
				float luminance = 0.2126 * r + 0.7152 * g + 0.0722 * b; // This formula is not very accurate, but it's good enough for this.

				if (luminance < 0.5)
				{
					validImage.setPixel(x, y, sf::Color::Black);
				}
			}
		}

		return validImage;
	}
}
