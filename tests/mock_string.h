#ifndef KRAKEN_MOCK_STRING_H
#define KRAKEN_MOCK_STRING_H

#include "kraken/decoder.h"

class MockString : public Kraken::Decoder {


    Kraken::element* _read;
    const unsigned int _n;

    inline const bool valid(const char* const p) const {
        return p >= reinterpret_cast<const char* const>(_read) &&
               p <  reinterpret_cast<const char* const>(_read + _n ) &&
             ( p -  reinterpret_cast<const char* const>(_read) ) % sizeof(Kraken::element) == 0;
    }

public:

    struct elem {
        Kraken::symbol _sym;
        bool _error;
        elem( bool );
        elem( Kraken::symbol );
        elem( int );
    };

    MockString( const std::initializer_list<elem> &r );

    ~MockString();

    const Kraken::element read(const char* const) const;

    operator const char* const () const;

};

#endif