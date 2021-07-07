#ifndef KLADIATORS_RULESET_HPP
#define KLADIATORS_RULESET_HPP

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
