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

		public:
		kcav();

		int run(int argc, char* argv[]);

		private:
		void setup_options();
		boost::program_options::options_description create_hidden_options();
		boost::program_options::options_description create_visible_options();
	};
}

#endif
