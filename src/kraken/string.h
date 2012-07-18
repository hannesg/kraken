#ifndef KRAKEN_STRING_H
#define KRAKEN_STRING_H

#include "kraken/base.h"

namespace Kraken {

  struct read{
    symbol _sym;
    bool _err;
    size_t _size;
  };

  class string;

  class string_private {

    virtual Kraken::read read() = 0;
    virtual string_private* operator+(const size_t) = 0;
  
    friend class string;

  };

  class string {
    string_private* _inner;
    string( string_private* );
  public:
    string( const string& s );
    string();
    inline bool valid() const {
      return _inner != nullptr;
    }
    inline operator bool() const{
      return _inner != nullptr;
    }
    inline const Kraken::read read() const {
      return _inner->read();
    }
    inline const string operator+(const size_t t) const{
      return string( _inner + t );
    }
  };

}
#endif