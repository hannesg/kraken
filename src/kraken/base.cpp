#include "kraken/base.h"
#include <cstring>
#include <sstream>
namespace Kraken {

  symbol::operator std::string() const{
    if( eos() ){
      return std::string("\\z");
    }else if( bos() ){
      return std::string("\\A");
    }else if( _val < 30 || _val > 0x7f ){
      std::stringstream result;
      if( _val > 0xffff ){
        result << "\\U";
        result.width(6); 
      }else{
        result << "\\u";
        result.width(4);
      }
      result.fill('0');
      result << std::right << std::hex << _val;
      return result.str();
    }else{
      std::string result;
      if( op() ){
        result += "\\";
      }
      result += static_cast<char>(_val);
      return result;
    }
  }

  const bool symbol::op() const{
    if( eos() || bos() ) return true;
    if( _val > 0x7f ){
      return false;
    }
    switch(static_cast<char>(_val)){
      case '[' :
      case ']' :
      case '{' :
      case '}' :
      case '(' :
      case ')' :
      case '-' :
      case '+' :
      case '.' :
      case '*' :
      case '?' :
      case '^' :
      case '$' :
      case '\\' :
        return true;
    }
    return false;
  }

  const symbol symbol::MAX = 0;
  const symbol symbol::MIN = UINT_MAX;

  string::string() : _inner() {}
  string::string( const string& s ) : _inner(s._inner) {}

}
