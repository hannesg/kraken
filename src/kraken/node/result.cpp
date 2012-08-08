#include "kraken/node/result.h"
namespace Kraken {

Node::Result::Result( TYPE t, size_t bs, std::string err, Node* node, fork_function ff ) :
  _type( t ),
  _bytesize( bs ),
  _error( err ),
  _next( node ),
  _fork( ff )
  {
}

Node::Result::Result( Node* node, size_t size ) : 
  _type( node ? CONTINUATION : FAIL ),
  _bytesize( node ? size : 0 ),
  _error(),
  _next(node),
  _fork() {
}

Node::Result::Result( Node* node, const std::function<const Node::Result(const Kraken::Decoder&, const char* const)> fork, size_t size ) :
  _type(CONTINUATION),
  _bytesize(size),
  _error(),
  _next(node),
  _fork(fork) {
}

Node::Result::Result( Node* node, Node* fork, size_t size ) :
  _type(CONTINUATION),
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

const Node::Result& Node::Result::fail(){
  static const Node::Result fail(FAIL);
  return fail;
}

const Node::Result& Node::Result::success(){
  static const Node::Result success(SUCCESS);
  return success;
}

//const Node::Result Node::Result::fail = Node::Result(nullptr);

}