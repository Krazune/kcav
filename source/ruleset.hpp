#ifndef RULESET_HPP
#define RULESET_HPP

#include <vector>

#include <SFML/Graphics.hpp>

namespace kcav
{
	class ruleset
	{
		public:
		virtual sf::Color get_state(sf::Color selfState, std::vector<sf::Color> neighbors) = 0;
	};
}

#endif
