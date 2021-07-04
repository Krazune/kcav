#include <memory>

#include "cellular_automata_engine.hpp"
#include "cellular_automaton.hpp"

namespace kcav
{
	cellular_automata_engine::cellular_automata_engine(std::unique_ptr<cellular_automaton> cellullarAutomaton, sf::Image inputGeneration) : cellullarAutomaton(std::move(cellullarAutomaton))
	{
		generation = inputGeneration;
	}

	void cellular_automata_engine::update_generation()
	{
		generation = cellullarAutomaton->get_next_generation(generation);
	}

	sf::Image cellular_automata_engine::get_generation() const
	{
		return generation;
	}
}
