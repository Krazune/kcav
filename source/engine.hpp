#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <memory>

#include <SFML/Graphics.hpp>

#include "cellular_automaton.hpp"

namespace kcav
{
	class engine
	{
		sf::Image generation;
		std::unique_ptr<cellular_automaton> cellullarAutomaton;

		public:
		engine(std::unique_ptr<cellular_automaton> cellullarAutomaton, sf::Image inputGeneration);

		void update_generation();

		sf::Image get_generation() const;
	};
}

#endif
