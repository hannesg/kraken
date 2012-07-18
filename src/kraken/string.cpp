#include "kraken/string.h"
namespace Kraken {

  string::string() : _inner() {

  }
  string::string( const string& s ) : _inner(s._inner) {
  	
  }

}