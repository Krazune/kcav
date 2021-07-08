#ifndef KCAV_ENGINE_HPP
#define KCAV_ENGINE_HPP

#include <memory>

#include <SFML/Graphics.hpp>

#include "cellular_automaton.hpp"

namespace kcav
{
	class engine
	{
		sf::Image gen;
		std::unique_ptr<cellular_automaton> automaton;

		public:
		engine(std::unique_ptr<cellular_automaton> automaton, sf::Image inputGen);

		void update_gen();

		sf::Image get_gen() const;
	};
}

#endif
