#include "parse_Bsm.hpp"

// This is an example of how you would parse a file and print its AST.

int main()
{
	try
	{
		auto a = Bsm::Parse("test.Bsm");
		std::wcout << Bsm::Jsonify(a).serialize() << std::endl;
		return EXIT_SUCCESS;
	}
	catch(Bsm::FileNotFoundException e)
	{
		std::wcout << "File test.Bsm not found." << std::endl;
	}
	catch(Bsm::ParserException e)
	{
		std::wcout << e.GetMessage() << std::endl;
	}
	return EXIT_SUCCESS;
}
