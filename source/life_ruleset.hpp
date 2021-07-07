#ifndef LIFE_RULESET_HPP
#define LIFE_RULESET_HPP

#include "ruleset.hpp"

namespace kcav
{
	class life_ruleset : public ruleset
	{
		public:
		sf::Color get_state(sf::Color selfState, std::vector<sf::Color> neighbors) override;

		bool has_invalid_states(const sf::Image& image) override;
		sf::Image convert_invalid_states(const sf::Image& original) override;
	};
}

#endif