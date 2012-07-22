#include "kraken/link.h"
#include <vector>
#include <thread>

void release_link(Kraken::Link* lnk){
	for( int j = 0 ; j < 4 ; j++ ){
		lnk->release();
	}
}

void test_link(){
	Kraken::Link* root = new Kraken::Link("","");
	Kraken::Link* lnk = new Kraken::Link(root,"");
	std::vector<std::thread*> trd;

	for( int i = 0 ; i < 20 ; i++ ){
		lnk->acquire();
	}
	for( int i = 0 ; i < 5 ; i++ ){
		trd.push_back( new std::thread(release_link, lnk) );
	}

	for( std::thread* t : trd ){
		t->join();
		delete t;
	}
}

int main( int argc, char** argv ){
	
	for( int i = 0 ; i < 100 ; i++ ){
		test_link();
	}
	return 0;
}