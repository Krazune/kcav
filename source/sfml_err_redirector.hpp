#ifndef KCAV_SFML_ERR_REDIRECTOR_HPP
#define KCAV_SFML_ERR_REDIRECTOR_HPP

#include <streambuf>

namespace kcav
{
	// Inspired by Plinth's err blocker created by Hapaxia (https://github.com/Hapaxia/Plinth/blob/master/Plinth/Sfml/ErrBlocker.hpp).
	class sfml_err_redirector
	{
		private:
		std::streambuf* backupStream;

		public:
		sfml_err_redirector(std::streambuf* newStream);

		~sfml_err_redirector();
	};
}

#endif
