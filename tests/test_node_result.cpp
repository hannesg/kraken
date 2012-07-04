#include "kraken/node.h"
#include "kraken/node/result.h"
#include <iostream>

int test_result_from_error(){

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

}

int test_result_from_nullptr(){
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
}

int main(int argc, char** argv){
	test_result_from_error();
	test_result_from_nullptr();
	std::cout << "\n";
	return 0;
}