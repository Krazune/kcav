#ifndef CELLULAR_AUTOMATON_HPP
#define CELLULAR_AUTOMATON_HPP

#include <memory>

#include <SFML/Graphics.hpp>

#include "ruleset.hpp"
#include "neighbors_selector.hpp"

namespace kcav
{
	class cellular_automaton
	{
		std::unique_ptr<ruleset> automatonRuleset;
		std::unique_ptr<neighbors_selector> neighborsSelector;

		public:
		cellular_automaton(std::unique_ptr<ruleset> ruleset, std::unique_ptr<neighbors_selector> neighborsSelector);

		sf::Image get_next_generation(const sf::Image& currentGeneration);

		sf::Image convert_invalid_states(const sf::Image& original);
	};
}

#endif
