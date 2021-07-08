#include <vector>

#include <SFML/Graphics.hpp>

#include "pilots_ruleset.hpp"

namespace kcav
{
	sf::Color pilots_ruleset::get_state(sf::Color selfState, std::vector<sf::Color> neighbors)
	{
		if (selfState == sf::Color::Black)
		{
			return sf::Color::Black;
		}

		bool redComing = neighbors[3] == sf::Color::Red;
		bool greenComing = neighbors[1] == sf::Color::Green;
		bool blueComing = neighbors[0] == sf::Color::Blue;
		bool yellownComing = neighbors[2] == sf::Color::Yellow;

		int comingCount = 0;

		if (redComing)
		{
			++comingCount;
		}

		if (greenComing)
		{
			++comingCount;
		}

		if (blueComing)
		{
			++comingCount;
		}

		if (yellownComing)
		{
			++comingCount;
		}

		if (comingCount == 1)
		{
			if (redComing)
			{
				return sf::Color::Red;
			}

			if (greenComing)
			{
				return sf::Color::Green;
			}

			if (blueComing)
			{
				return sf::Color::Blue;
			}

			if (yellownComing)
			{
				return sf::Color::Yellow;
			}
		}
		else if (comingCount > 1)
		{
			return sf::Color::Black;
		}

		return sf::Color::White;
	}

	bool pilots_ruleset::has_invalid_states(const sf::Image& image)
	{
		unsigned int width = image.getSize().x;
		unsigned int height = image.getSize().y;

		for (unsigned int x = 0; x < width; ++x)
		{
			for (unsigned int y = 0; y < height; ++y)
			{
				sf::Color state = image.getPixel(x, y);

				if (state != sf::Color::Black &&
					state != sf::Color::White &&
					state != sf::Color::Red &&
					state != sf::Color::Green &&
					state != sf::Color::Blue &&
					state != sf::Color::Yellow)
				{
					return false;
				}
			}
		}

		return true;
	}

	sf::Image pilots_ruleset::convert_invalid_states(const sf::Image& original)
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

				if (state == sf::Color::Black)
				{
					continue;
				}

				if (state.r > state.g && state.r > state.b && state.r > 127)
				{
					validImage.setPixel(x, y, sf::Color::Red);

					continue;
				}

				if (state.g > state.r && state.g > state.b && state.g > 127)
				{
					validImage.setPixel(x, y, sf::Color::Green);

					continue;
				}

				if (state.b > state.r && state.b > state.g && state.b > 127)
				{
					validImage.setPixel(x, y, sf::Color::Blue);

					continue;
				}

				validImage.setPixel(x, y, sf::Color::White);
			}
		}

		return validImage;
	}
}
