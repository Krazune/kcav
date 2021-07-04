#ifndef CELLULAR_AUTOMATA_ENGINE_HPP
#define CELLULAR_AUTOMATA_ENGINE_HPP

#include <memory>

#include <SFML/Graphics.hpp>

#include "cellular_automaton.hpp"

namespace kcav
{
	class cellular_automata_engine
	{
		sf::Image generation;
		std::unique_ptr<cellular_automaton> cellullarAutomaton;

		public:
		cellular_automata_engine(std::unique_ptr<cellular_automaton> cellullarAutomaton, sf::Image inputGeneration);

		void update_generation();

		sf::Image get_generation() const;
	};
}

#endif
