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

  std::ostream& operator<<(std::ostream& io, symbol s){
    return io << s.operator std::string();
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
  const symbol symbol::EOS = 0;

  element::element() : _sym(symbol::EOS), _size(0), _error(true) {};

  element::element( symbol sym , size_t size ) : _sym(sym), _size(size), _error(false) {};

}
