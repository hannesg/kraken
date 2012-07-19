#ifndef KRAKEN_STRING_H
#define KRAKEN_STRING_H

#include "kraken/base.h"

namespace Kraken {

  struct read{
    symbol _sym;
    bool _error;
    size_t _size;
    read() : _sym(0), _error(true), _size(0) {
    }
    read(symbol s, size_t size = 1) : _sym(s), _error(false), _size(size) {
    }
  };

  class string;

  class string_private {

  public:
    virtual ~string_private(){};
    virtual Kraken::read read() const = 0;
    virtual string_private* operator+(const size_t) const = 0;
    virtual bool valid() const;

  };

  class invalid_string_private : public string_private {

  public:
    virtual Kraken::read read() const ;
    virtual string_private* operator+(const size_t) const ;
    virtual bool valid() const;

  };

  class string {
    string_private* _inner;
  public:
    string( string_private* );
    string( const string& s );
    string();
    ~string();
    inline bool valid() const {
      return _inner->valid();
    }
    inline operator bool() const{
      return _inner->valid();
    }
    inline const Kraken::read read() const {
      return _inner->read();
    }
    inline const string advance(const size_t t) const{
      return string( _inner + t );
    }
  };

}
#endif