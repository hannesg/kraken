#include "kraken/string.h"
#include "mock_string.h"
#include "kraken/node/map.h"
#include "kraken/node/terminal.h"
#include <iostream>

void test_node_map1(){
	Kraken::Node::Pool pool;
	Kraken::Node::Map* node = pool.make<Kraken::Node::Map>();
	mock_string s = { Kraken::read(15) };

	node->set( 10, 20, pool.make<Kraken::Node::Terminal>(1) );
	Kraken::Node::Result result = node->traverse(&s);

	if( result.isSuccess() ){
		std::cout << ".";
	}else{
		std::cout << "Result wasn't success.";
	}
}

void test_node_map2(){
	Kraken::Node::Pool pool;
	Kraken::Node::Map* node = pool.make<Kraken::Node::Map>();
	mock_string s = { Kraken::read(5) };

	node->set( 10, 20, pool.make<Kraken::Node::Terminal>(1) );
	Kraken::Node::Result result = node->traverse(&s);

	if( result.isFail() ){
		std::cout << ".";
	}else{
		std::cout << "Result wasn't fail.";
	}
}

int main(int argc, char** argv){
	test_node_map1();
	test_node_map2();
	return 0;
}