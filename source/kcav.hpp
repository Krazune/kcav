#ifndef KCAV_HPP
#define KCAV_HPP

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

		boost::program_options::options_description options;
		boost::program_options::options_description hiddenOptions;
		boost::program_options::options_description visibleOptions;
		boost::program_options::positional_options_description positionalOptions;

		boost::program_options::variables_map optionsMap;

		sf::Image generation;

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

		void store_options(int argc, char* argv[]);

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
