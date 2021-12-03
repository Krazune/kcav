/*
	MIT License

	Copyright (c) 2021 Miguel Sousa

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/
#ifndef KCAV_KCAV_HPP
#define KCAV_KCAV_HPP

#include <memory>
#include <vector>

#include <boost/program_options.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "cellular_automaton.hpp"

namespace kcav
{
	class kcav
	{
		private:
		static std::vector<sf::Vector2<int>> mooreNeighbors;
		static std::vector<sf::Vector2<int>> vonNeumannNeighbors;
		static std::vector<sf::Vector2<int>> immediateNeighbors;

		boost::program_options::options_description options;
		boost::program_options::options_description hiddenOptions;
		boost::program_options::options_description visibleOptions;
		boost::program_options::positional_options_description positionalOptions;

		boost::program_options::variables_map optionsMap;

		sf::Image gen;

		std::unique_ptr<cellular_automaton> cellularAutomaton;

		int millisecondsPerGeneration = 0;

		public:
		kcav();

		int run(int argc, char* argv[]);

		private:
		void setup_options();
		void setup_hidden_options();
		void setup_visible_options();
		void setup_positional_options();

		void setup_options_map(int argc, char* argv[]);

		bool setup_cellular_automaton();
		bool setup_generation_time();

		bool process_option_storage(int argc, char* argv[]);
		bool process_secondary_usages() const;
		bool process_options_notification();

		bool load_image_file();

		void run_engine_loop();

		void handle_program_options_exceptions() const;
		void print_help_message() const;
		void print_version_message() const;
		void print_file_load_error_message() const;
		void print_invalid_identifier_error_message() const;
		void print_invalid_time_error_message() const;
	};
}

#endif
