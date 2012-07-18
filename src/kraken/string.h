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
  
    friend class string;

  };

  class string {
    string_private* _inner;
  public:
    string( const string& s );
    string();
    inline Kraken::read read(){
      return _inner->read();
    }
  };

}
#endif