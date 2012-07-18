#include "kraken/base.h"
#include "kraken/node.h"
#include "kraken/node/result.h"
#include "kraken/node/terminal.h"
#include <iostream>

void test_result_from_error(){

	Kraken::Node::Result res = "This is borked";
	
	if( !res.isError() ){
		std::cout << "Result from string should be an error\n";
	}else{
		std::cout << ".";
	}
	if( res.error() != "This is borked" ){
		std::cout << "Result from string had wrong message string";
	}else{
		std::cout << ".";
	}
	if( res ){
		std::cout << "Result from string evaled to true";
	}else{
		std::cout << ".";
	}
	if( res.hasFork() ){
		std::cout << "Result from string has a fork";
	}else{
		std::cout << ".";
	}
}

void test_result_from_nullptr(){
	Kraken::Node::Result res = nullptr;
	if( !res.isFail() ){
		std::cout << "Result from nullptr should be a fail\n";
	}else{
		std::cout << ".";
	}
	if( res ){
		std::cout << "Result from nullptr evaled to true";
	}else{
		std::cout << ".";
	}
	if( res.hasFork() ){
		std::cout << "Result from nullptr has a fork";
	}else{
		std::cout << ".";
	}
}

void test_result_from_node(){
	Kraken::Node* node = new Kraken::Node::Terminal(0);
	Kraken::Node::Result res = node;
	if( !res.isSuccess() ){
		std::cout << "Result from node should be a success\n";
	}else{
		std::cout << ".";
	}
	if( !res ){
		std::cout << "Result from node doesn't eval to true";
	}else{
		std::cout << ".";
	}
	if( res.hasFork() ){
		std::cout << "Result from node has a fork";
	}else{
		std::cout << ".";
	}
	delete node;
}

void test_result_from_node_and_fork(){
	Kraken::Node* node = new Kraken::Node::Terminal(0);
	Kraken::Node::Result res = Kraken::Node::Result( node, node->bindTraverse() );
	if( !res.isSuccess() ){
		std::cout << "Result from node and fork should be a success\n";
	}else{
		std::cout << ".";
	}
	if( !res ){
		std::cout << "Result from node and fork didn't eval to true";
	}else{
		std::cout << ".";
	}
	if( !res.hasFork() ){
		std::cout << "Result from node and fork doesn't have a fork";
	}else{
		std::cout << ".";
	}
	delete node;
}

int main(int argc, char** argv){
	test_result_from_error();
	test_result_from_nullptr();
	test_result_from_node();
	test_result_from_node_and_fork();
	std::cout << "\n";
	return 0;
}