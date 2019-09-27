
#include "parse_bsm.hpp"

/*
	WARNING: This file is generated using ruco. Please modify the .ruco file if you wish to change anything
	https://github.com/davidsiaw/ruco
*/

namespace Bsm
{
	BsmPtr Parse(std::string sourceFile)
	{
		std::shared_ptr<FILE> fp (fopen(sourceFile.c_str(), "r"), fclose);
		if (!fp)
		{
			throw FileNotFoundException();
		}
		std::shared_ptr<Scanner> scanner (new Scanner(fp.get()));
		std::shared_ptr<Parser> parser (new Parser(scanner.get()));
		parser->Parse();

		return parser->bsm;
	}

	picojson::object CompileBsm(BsmPtr pointer);
	picojson::object CompileHexLit(HexLitPtr pointer);

	picojson::object CompileBsm(BsmPtr pointer)
	{
		picojson::object object;

		// normal
		object[L"_type"] = picojson::value(L"Bsm");
		object[L"_col"] = picojson::value((double)pointer->_col);
		object[L"_line"] = picojson::value((double)pointer->_line);
		

		// {:count=>3, :type=>:id}

		picojson::array hexlits;

		for(unsigned i=0; i<pointer->hexlits.size(); i++)
		{
			hexlits.push_back(picojson::value(CompileHexLit(pointer->hexlits[i])));
		}

		object[L"hexlits"] = picojson::value(hexlits);




		return object;
	}

	picojson::object CompileHexLit(HexLitPtr pointer)
	{
		picojson::object object;

		// normal
		object[L"_type"] = picojson::value(L"HexLit");
		object[L"_col"] = picojson::value((double)pointer->_col);
		object[L"_line"] = picojson::value((double)pointer->_line);
		

		// {:count=>1, :type=>:token}
		object[L"_token"] = picojson::value(pointer->content);




		return object;
	}



	picojson::value Jsonify(BsmPtr parseResult)
	{
		return picojson::value(CompileBsm(parseResult));
	}

}

