#ifndef CELLULAR_AUTOMATON_HPP
#define CELLULAR_AUTOMATON_HPP

#include <memory>

#include <SFML/Graphics.hpp>

namespace kcav
{
	class ruleset;
	class neighbors_selector;

	class cellular_automaton
	{
		std::unique_ptr<ruleset> automatonRuleset;
		std::unique_ptr<neighbors_selector> neighborsSelector;

		public:
		cellular_automaton(std::unique_ptr<ruleset> ruleset, std::unique_ptr<neighbors_selector> neighborsSelector);

		sf::Image get_next_generation(const sf::Image& currentGeneration);
	};
}

#endif
