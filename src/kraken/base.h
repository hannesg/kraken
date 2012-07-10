#ifndef KRAKEN_BASE_H
#define KRAKEN_BASE_H
#include <string>
#include <climits>
namespace Kraken {

  class symbol{
    unsigned int _val;
  public:
    inline symbol(int v) : _val(static_cast<unsigned int>(v)) {};
    inline symbol(unsigned int v) : _val(v) {};
    inline symbol(const symbol& s ) : _val(s._val) {};
    inline symbol(char c) : _val(c) {};
    inline symbol operator=(const symbol& s){ _val = s._val; return *this; };
    operator std::string() const;
    explicit inline operator unsigned int() const { return _val; };
    inline bool operator!=( const symbol s ) const { return _val != s._val; };
    inline bool operator==( const symbol s ) const { return _val == s._val; };
    inline bool operator<( const symbol s ) const { return _val < s._val; };
    inline bool operator>( const symbol s ) const { return _val > s._val; };
    inline bool operator<=( const symbol s ) const { return _val <= s._val; };
    inline bool operator>=( const symbol s ) const { return _val >= s._val; };
    inline const symbol operator-( const unsigned int i ) const { return symbol(_val - i); };
    inline const symbol operator+( const unsigned int i ) const { return symbol(_val + i); };
    inline const bool eos() const { return _val == 0; };
    inline const bool bos() const { return _val == UINT_MAX; };
    const bool op() const;

    static const symbol MAX;
    static const symbol MIN;

  };

  typedef unsigned short tentacle_id;

  class string {

  };

  enum encoding_id {
    GENERIC, UTF8
  };

  template<encoding_id e>
  class encoding {
    public:
    typedef typename Kraken::symbol symbol;
  };

  template<>
  class encoding<UTF8> {
    public:
    typedef unsigned char symbol;
  };

}
#endif
