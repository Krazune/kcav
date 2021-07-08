#include <memory>
#include <utility>

#include <SFML/Graphics.hpp>

#include "engine.hpp"
#include "cellular_automaton.hpp"

namespace kcav
{
	engine::engine(std::unique_ptr<cellular_automaton> automaton, sf::Image inputGen) :
		automaton(std::move(automaton))
	{
		gen = this->automaton->convert_invalid_states(inputGen);
	}

	void engine::update_gen()
	{
		gen = automaton->get_next_gen(gen);
	}

	sf::Image engine::get_gen() const
	{
		return gen;
	}
}
