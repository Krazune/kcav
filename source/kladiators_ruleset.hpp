#ifndef KCAV_KLADIATORS_RULESET_HPP
#define KCAV_KLADIATORS_RULESET_HPP

#include <memory>

#include <SFML/Graphics.hpp>

#include "ruleset.hpp"

namespace kcav
{
	class kladiators_ruleset : public ruleset
	{
		public:
		sf::Color get_state(sf::Color selfState, std::vector<sf::Color> neighbors) override;
	};
}

#endif
