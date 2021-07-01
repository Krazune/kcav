#include "life_ruleset.hpp"

namespace kcav
{
	sf::Color kcav::life_ruleset::get_state(sf::Color selfState, std::vector<sf::Color> neighbors)
	{
		int neighborCount = 0;

		for (int i = 0; i < 8; ++i)
		{
			if (neighbors[i] == sf::Color::Black)
			{
				++neighborCount;
			}
		}

		if (neighborCount == 2)
		{
			return selfState;
		}

		if (neighborCount == 3)
		{
			return sf::Color::Black;
		}

		return sf::Color::White;
	}
}

