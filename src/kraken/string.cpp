#include "kraken/string.h"
namespace Kraken {

  string::string() : _inner(new invalid_string_private()) {
  }

  string::~string(){
  	//delete _inner;
  }

  string::string( const string& s ) : _inner(s._inner) {

  }
  string::string( string_private* inner ) : _inner(inner == nullptr ? new invalid_string_private() : inner) {
  }

  bool string_private::valid() const {
  	return true;
  }

  Kraken::read invalid_string_private::read() const {
  	return Kraken::read();
  }

  string_private* invalid_string_private::operator+(const size_t) const  {
  	return new invalid_string_private();
  }

  bool invalid_string_private::valid() const {
  	return false;
  }

}