#ifndef KCAV_CELLULAR_AUTOMATON_HPP
#define KCAV_CELLULAR_AUTOMATON_HPP

#include <memory>

#include <SFML/Graphics.hpp>

#include "neighbors_selector.hpp"
#include "ruleset.hpp"

namespace kcav
{
	class cellular_automaton
	{
		std::unique_ptr<ruleset> automatonRuleset;
		std::unique_ptr<neighbors_selector> neighborsSelector;

		public:
		cellular_automaton(std::unique_ptr<ruleset> ruleset, std::unique_ptr<neighbors_selector> neighborsSelector);

		sf::Image get_next_gen(const sf::Image& currentGen);

		sf::Image convert_invalid_states(const sf::Image& original);
	};
}

#endif
