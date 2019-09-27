
#ifndef PARSE_BSM_HPP
#define PARSE_BSM_HPP

/*
	WARNING: This file is generated using ruco. Please modify the .ruco file if you wish to change anything
	https://github.com/davidsiaw/ruco
*/

#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

#include "Scanner.h"
#include "Parser.h"

#include "picojson.hpp"

namespace Bsm
{
	/**
	 * Exception thrown when the specified source file is not found
	 */
	class FileNotFoundException {};

	/**
	 * Parses a source file into the data structure of Bsm
	 */
	BsmPtr Parse(std::string sourceFile);

	/**
	 * Transforms the data structure of Bsm to an abstract syntax tree in JSON format
	 */
	picojson::value Jsonify(BsmPtr parseResult);
}

#endif // PARSE_BSM_HPP

