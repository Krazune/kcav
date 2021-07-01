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

		virtual	bool has_invalid_states(const sf::Image& image);
		virtual sf::Image convert_invalid_states(const sf::Image& original);
	};
}

#endif
