#include "mock_string.h"


mock_string::mock_string( Kraken::read* read, unsigned int n ) : _read(read), _n(n), _allocated(false) {
}

mock_string::mock_string( const std::initializer_list<Kraken::read> &r ) : _read(nullptr), _n( r.size() ), _allocated(true) {
    _read = new Kraken::read[ r.size() ];
    std::copy( r.begin(), r.end(), _read );
}

mock_string::~mock_string(){
    if( _allocated ){
        delete[] _read;
    }
}

Kraken::read mock_string::read() const {
    return *_read;
}

Kraken::string_private* mock_string::operator+(const size_t s) const {
    int t = s;
    unsigned int n = _n;
    Kraken::read* read = _read;
    while( t > 0 && n > 0){
        t -= read->_size;
        read++;
        n--;
    }
    if( t != 0 ){
        return nullptr;
    }
    return new mock_string( read, n );
}