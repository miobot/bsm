

#if !defined(Bsm_COCO_PARSER_H__)
#define Bsm_COCO_PARSER_H__

#include <iostream>
#include <memory>
#include "Bsm.hpp"


#include "Scanner.h"

namespace Bsm {


class ParserException {

	int line,col;
	std::wstring message;

public:
	ParserException(int line, int col, std::wstring message) :
	line(line), col(col), message(message)
	{
	}

	int LineNumber() const
	{
		return line;
	}

	int ColumnNumber() const
	{
		return col;
	}

	std::wstring GetMessage() const
	{
		return message;
	}
};

class Errors {
public:
	int count;			// number of errors detected
	std::vector<ParserException> warnings;

	Errors();
	void SynErr(int line, int col, int n);
	void Error(int line, int col, const wchar_t *s);
	void Warning(int line, int col, const wchar_t *s);
	void Warning(const wchar_t *s);
	void Exception(const wchar_t *s);

}; // Errors

class Parser {
private:
	enum {
		_EOF=0,
		_customTokenHexLit=1,
		_ddtSym=3,
		_optionSym=4
	};
	int maxT;

	Token *dummyToken;
	int errDist;
	int minErrDist;

	void SynErr(int n);
	void Get();
	void Expect(int n);
	bool StartOf(int s);
	void ExpectWeak(int n, int follow);
	bool WeakSeparator(int n, int syFol, int repFol);

public:
	Scanner *scanner;
	Errors  *errors;

	Token *t;			// last recognized token
	Token *la;			// lookahead token

BsmPtr bsm;



	Parser(Scanner *scanner);
	~Parser();
	void SemErr(const wchar_t* msg);

	void Bsm();
	void HexLit(HexLitPtr& production);

	void Parse();

}; // end Parser

} // namespace


#endif

