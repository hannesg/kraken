#include "kraken.h"
#include "kraken/string.h"
#include <iostream>
#include <array>

class mock_string : public Kraken::string_private {

	Kraken::read* _read;
	unsigned int _n;
	bool _allocated;

	mock_string( Kraken::read* read, unsigned int n ) : _read(read), _n(n), _allocated(false) {
	}

public:

	mock_string( const std::initializer_list<Kraken::read> &r ) : _read(nullptr), _n( r.size() ), _allocated(true) {
		_read = new Kraken::read[ r.size() ];
		std::copy( r.begin(), r.end(), _read );
	}

	virtual ~mock_string(){
		if( _allocated ){
			delete[] _read;
		}
	}

	virtual Kraken::read read() const {
		return *_read;
	}
    virtual Kraken::string_private* operator+(const size_t s) const {
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

};


int main(int argc, char** argv){

	mock_string *ms = new mock_string( {
		Kraken::read( 1 ),
		Kraken::read( 2 ),
		Kraken::read( 3 )
	} );

	Kraken::string s = ms + 0;

	s = s.advance( 1 );

	s = s.advance( 2 );

	s = s.advance( 1 );

	delete ms;

	return 0;
}