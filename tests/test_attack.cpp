#include "kraken/base.h"
#include "mock_string.h"
#include "kraken/attack.h"
#include "kraken/the.h"
#include "kraken/node/map.h"
#include "kraken/node/terminal.h"
#include <iostream>
#include <array>

void test_attack1(){
	Kraken::Node::Pool pool;
	Kraken::Node::Map* root = pool.make<Kraken::Node::Map>();
	root->set(5,10, pool.make<Kraken::Node::Terminal>(0) );
	root->set(11, 20, pool.make<Kraken::Node::Terminal>(1) );
	Kraken::The the = Kraken::The( &pool, root );

	MockString ms = { 7 };

	Kraken::Attack attack = Kraken::Attack( &the, ms, ms );


}


int main(int argc, char** argv){

	test_attack1();

	return 0;
}