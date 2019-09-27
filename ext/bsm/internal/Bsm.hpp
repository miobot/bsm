
#ifndef BSM_HPP
#define BSM_HPP

/*
	WARNING: This file is generated using ruco. Please modify the .ruco file if you wish to change anything
	https://github.com/davidsiaw/ruco
*/

#include <string>
#include <memory>
#include <vector>

namespace Bsm
{

class HexLit 
{
public:
	unsigned _line, _col;
	std::wstring content;
};
typedef std::shared_ptr<HexLit> HexLitPtr;
typedef std::vector<HexLitPtr> HexLitArray;

class Bsm 
{
public:
	unsigned _line, _col;
	HexLitArray hexlits;
};
typedef std::shared_ptr<Bsm> BsmPtr;
typedef std::vector<BsmPtr> BsmArray;


}

#endif // BSM_HPP

