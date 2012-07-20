#ifndef KRAKEN_MOCK_STRING_H
#define KRAKEN_MOCK_STRING_H

#include "kraken/string.h"
class mock_string : public Kraken::string_private {

    Kraken::read* _read;
    unsigned int _n;
    bool _allocated;

    mock_string( Kraken::read* read, unsigned int n );

public:

    mock_string( const std::initializer_list<Kraken::read> &r );

    virtual ~mock_string();

    virtual Kraken::read read() const ;
    virtual Kraken::string_private* advance(const size_t s) const ;
    virtual bool valid() const ;

    bool allocated() const;

};

#endif