#include "kraken/base.h"
#include "mock_string.h"
#include "kraken/attack.h"
#include <iostream>
#include <array>


int main(int argc, char** argv){

	MockString *ms = new MockString( {
		1, 2, 3
	} );

	Kraken::element e = ms->read( *ms );

	std::cout << e._sym;
	
	//s = s.advance( 1 );

	delete ms;

	return 0;
}