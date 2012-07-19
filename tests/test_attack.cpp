#include "kraken.h"
#include "kraken/string.h"
#include "mock_string.h"
#include <iostream>
#include <array>


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