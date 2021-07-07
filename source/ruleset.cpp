#include "ruleset.hpp"

namespace kcav
{
	bool ruleset::has_invalid_states(const sf::Image& image)
	{
		return false;
	}

	sf::Image ruleset::convert_invalid_states(const sf::Image& original)
	{
		return original;
	}
}
