#include <memory>
#include <utility>

#include <SFML/Graphics.hpp>

#include "engine.hpp"
#include "cellular_automaton.hpp"

namespace kcav
{
	engine::engine(std::unique_ptr<cellular_automaton> cellullarAutomaton, sf::Image inputGeneration) : cellullarAutomaton(std::move(cellullarAutomaton))
	{
		generation = this->cellullarAutomaton->convert_invalid_states(inputGeneration);
	}

	void engine::update_generation()
	{
		generation = cellullarAutomaton->get_next_generation(generation);
	}

	sf::Image engine::get_generation() const
	{
		return generation;
	}
}
