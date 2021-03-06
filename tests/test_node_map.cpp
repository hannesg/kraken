#include "mock_string.h"
#include "kraken/node/map.h"
#include "kraken/node/terminal.h"
#include <iostream>

void test_node_map1(){
	Kraken::Node::Pool pool;
	Kraken::Node::Map* node = pool.make<Kraken::Node::Map>();
	MockString s = { 15 };

	node->set( 10, 20, pool.make<Kraken::Node::Terminal>(1) );
	Kraken::Node::Result result = node->traverse(s, s);

	if( result.isContinuation() ){
		std::cout << ".";
	}else{
		std::cout << "Result wasn't a continuation.";
	}
}

void test_node_map2(){
	Kraken::Node::Pool pool;
	Kraken::Node::Map* node = pool.make<Kraken::Node::Map>();
	MockString s = { 5 };

	node->set( 10, 20, pool.make<Kraken::Node::Terminal>(1) );
	Kraken::Node::Result result = node->traverse(s, s);

	if( result.isFail() ){
		std::cout << ".";
	}else{
		std::cout << "Result wasn't fail.";
	}
}

void test_node_map3(){
	Kraken::Node::Pool pool;
	Kraken::Node::Map* node = pool.make<Kraken::Node::Map>();
	MockString s = { };

	node->set( 10, 20, pool.make<Kraken::Node::Terminal>(1) );
	Kraken::Node::Result result = node->traverse(s, s);

	if( result.isError() ){
		std::cout << ".";
	}else{
		std::cout << "Result wasn't error.";
	}
}

int main(int argc, char** argv){
	test_node_map1();
	test_node_map2();
	test_node_map3();
	return 0;
}