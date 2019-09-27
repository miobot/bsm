#include <ruby.h>
#include "Parser.h"
#include "parse_Bsm.hpp"
#include "sstream"

picojson::value JsonifyParserError(Bsm::ParserException e)
{
  picojson::object error;
  error[L"_error"] = picojson::value(e.GetMessage());
  error[L"_line"] = picojson::value((double)e.LineNumber());
  error[L"_col"] = picojson::value((double)e.ColumnNumber());
  error[L"_type"] = picojson::value(L"parser");
  return picojson::value(error);
}

picojson::value JsonifyOtherError(std::wstring message)
{
  picojson::object error;
  error[L"_error"] = picojson::value(message);
  error[L"_type"] = picojson::value(L"other");
  return picojson::value(error);
}


std::wstring RSTRING_PTR_WIDE(VALUE rubyString)
{
  std::wstring wc( RSTRING_LEN(rubyString), L'#' );
  mbstowcs( &wc[0], RSTRING_PTR(rubyString), RSTRING_LEN(rubyString) );
  return wc;
}

VALUE rb_str_new_wide(std::wstring str)
{
  std::string s( str.begin(), str.end() );
  return rb_str_new(s.c_str(), s.length());
}

VALUE method_test(VALUE rubySelf, VALUE rubyString)
{
  std::wstring s(RSTRING_PTR_WIDE(rubyString));
  s = L"test-" + s;
  
  return rb_str_new_wide(s);
}

VALUE method_compile_to_ast(VALUE rubySelf, VALUE rubyString)
{
  try
  {
    Bsm::Scanner scanner(RSTRING_PTR(rubyString), RSTRING_LEN(rubyString));
    Bsm::Parser parser(&scanner);
    parser.Parse();
    auto json = Bsm::Jsonify(parser.bsm);
    return rb_str_new_wide(json.serialize().c_str());
  }
  catch (Bsm::ParserException e)
  {
    auto str = JsonifyParserError(e).serialize();
    return rb_str_new_wide(str.c_str());
  }

  return rb_str_new_wide(L"{}");
}

extern "C" void Init_internal()
{
  VALUE bsm = rb_define_module("Bsm");
  VALUE bsm_parse = rb_define_module_under(bsm, "BsmParse");
  rb_define_singleton_method(bsm_parse, "bsm_parse_test", (VALUE(*)(ANYARGS))method_test,1);
  rb_define_singleton_method(bsm_parse, "bsm_parse_compile_to_ast", (VALUE(*)(ANYARGS))method_compile_to_ast,1);
}