#include <SFML/System.hpp>

#include "sfml_err_redirector.hpp"

namespace kcav
{
	sfml_err_redirector::sfml_err_redirector(std::streambuf* newStream)
	{
		backupStream = sf::err().rdbuf();

		sf::err().rdbuf(newStream);
	}

	sfml_err_redirector::~sfml_err_redirector()
	{
		sf::err().rdbuf(backupStream);
	}
}
