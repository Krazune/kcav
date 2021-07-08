#ifndef SEEDS_RULESET_HPP
#define SEEDS_RULESET_HPP

#include <vector>

#include <SFML/Graphics.hpp>

#include "ruleset.hpp"

namespace kcav
{
	class seeds_ruleset : public ruleset
	{
		public:
		sf::Color get_state(sf::Color selfState, std::vector<sf::Color> neighbors) override;
		bool has_invalid_states(const sf::Image& image) override;
		sf::Image convert_invalid_states(const sf::Image& original) override;
	};
}

#endif
