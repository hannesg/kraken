#include "kraken/node/result.h"
namespace Kraken {

Node::Result::Result( Node* node, size_t size ) : 
  _type(SUCCESS),
  _bytesize(size),
  _error(),
  _next(node),
  _fork() {
}

Node::Result::Result( Node* node, const std::function<const Node::Result(const Kraken::string)> fork, size_t size ) :
  _type(SUCCESS),
  _bytesize(size),
  _error(),
  _next(node),
  _fork(fork) {
}

Node::Result::Result( Node* node, Node* fork, size_t size ) :
  _type(SUCCESS),
  _bytesize(size),
  _error(),
  _next(node),
  _fork(fork->bindTraverse()) {
}

Node::Result::Result( std::string str ) :
  _type(ERROR),
  _bytesize(0),
  _error(str),
  _next(nullptr),
  _fork(){
}

Node::Result::Result( const char* str ) :
  _type(ERROR),
  _bytesize(0),
  _error(str),
  _next(nullptr),
  _fork(){
}

Node::Result::Result( std::nullptr_t ) :
  _type(FAIL),
  _bytesize(0),
  _error(),
  _next(nullptr),
  _fork() {
}

const Node::Result Node::Result::fail = Node::Result(nullptr);

}