#ifndef KCAV_HPP
#define KCAV_HPP

#include <vector>

#include <boost/program_options.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

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

		public:
		kcav();

		int run(int argc, char* argv[]);

		private:
		void setup_options();
		void setup_hidden_options();
		void setup_visible_options();
		void setup_positional_options();

		void store_options(int argc, char* argv[]);

		bool process_secondary_usages() const;

		bool load_image_file();

		void handle_program_options_exceptions() const;
		void print_help_message() const;
		void print_version_message() const;
		void print_file_load_error_message() const;
	};
}

#endif
