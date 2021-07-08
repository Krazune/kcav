#include <vector>

#include <SFML/Graphics.hpp>

#include "kladiators_ruleset.hpp"

namespace kcav
{
	sf::Color kcav::kladiators_ruleset::get_state(sf::Color selfState, std::vector<sf::Color> neighbors)
	{
		sf::Color state = sf::Color::Black;
		int rgbSum = 0;

		for (int i = 0; i < 8; ++i)
		{
			int newSum = neighbors[i].r + neighbors[i].g + neighbors[i].b;

			if (newSum > rgbSum)
			{
				rgbSum = newSum;
				state = neighbors[i];
			}
		}

		return state;
	}
}
