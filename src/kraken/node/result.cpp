#include "kraken/node/result.h"
namespace Kraken {

Node::Result::Result( Node* node, size_t size ) : 
  _next(node),
  _type(HIT),
  _bytesize(size),
  _error() {
}

Node::Result::Result( Node* node, std::function<const Node::Result(std::string)> /*fork*/, size_t size ) :
  _next(node),
  /*_fork(fork),*/
  _type(HIT),
  _bytesize(size),
  _error() {
}

Node::Result::Result( std::string str ) :
  _next(nullptr),
  _type(ERROR),
  _bytesize(0),
  _error(str){
}

Node::Result::Result( const char* str ) :
  _next(nullptr),
  _type(ERROR), 
  _bytesize(0), 
  _error(str){
}

Node::Result::Result( std::nullptr_t ) :
  _next(nullptr),
  _bytesize(0),
  _type(FAIL),
  _error() {
}

const Node::Result Node::Result::fail = Node::Result(nullptr);

}