#include "kraken/string.h"
#include <iostream>
namespace Kraken {

  string::string() : _inner(new invalid_string_private()) {
  }

  string::~string(){
    delete _inner;
  }


  string::string( const string& s ) : _inner(s._inner->clone()) {
  }


  string::string( string&& s ) : _inner(s._inner) {
    s._inner = nullptr;
  }

  string::string( string_private* inner ) : _inner(inner == nullptr ? new invalid_string_private() : inner) {
  }

  const string string::operator=( const string s ){
    delete _inner;
    _inner = s._inner;
    return *this;
  }

  bool string_private::valid() const {
  	return true;
  }

  string_private* string_private::clone() const  {
    return advance(0);
  }


  Kraken::read invalid_string_private::read() const {
  	return Kraken::read();
  }

  string_private* invalid_string_private::advance(const size_t) const  {
  	return new invalid_string_private();
  }

  bool invalid_string_private::valid() const {
  	return false;
  }

}