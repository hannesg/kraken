#include "mock_string.h"
#include <iostream>

const Kraken::element MockString::read(const char* const p ) const{
    if( valid(p) ){
        return *reinterpret_cast<const Kraken::element* const>(p);
    }else{
        return {};
    }
}

MockString::elem::elem( bool b ) : _sym(Kraken::symbol::EOS), _error(b) {};
MockString::elem::elem( Kraken::symbol sym ) : _sym(sym), _error(false) {};
MockString::elem::elem( int sym ) : _sym(sym), _error(false) {};

MockString::MockString( const std::initializer_list<MockString::elem> &r ) : _read(nullptr), _n( r.size() ) {
    if( _n ){
        Kraken::element* head = new Kraken::element[_n]();
        Kraken::element* p = head;
        for( auto e : r ){
            if( e._error ){
                *p = Kraken::element();
            }else{
                *p = Kraken::element(e._sym, sizeof(Kraken::element) );
            }
            p++;
        }
        _read = head;
    }
}

MockString::~MockString(){
    if( _n ){
        delete[] _read;
    }
}

MockString::operator const char* const () const{
    return reinterpret_cast<const char* const>(_read);
}
