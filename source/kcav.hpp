#ifndef KCAV_HPP
#define KCAV_HPP

#include <boost/program_options.hpp>

namespace kcav
{
	class kcav
	{
		private:
		boost::program_options::options_description options;
		boost::program_options::positional_options_description positionalOptions;

		boost::program_options::variables_map optionsMap;

		public:
		kcav();

		int run(int argc, char* argv[]);

		private:
		void setup_options();
		boost::program_options::options_description create_hidden_options() const;
		boost::program_options::options_description create_visible_options() const;
		boost::program_options::positional_options_description create_positional_options() const;

		void store_options(int argc, char* argv[]);

		void handle_program_options_exceptions() const;
		void print_usage_message() const;
	};
}

#endif
