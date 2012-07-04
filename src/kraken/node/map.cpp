#include "kraken/node/result.h"
#include "kraken/node/map.h"
namespace Kraken {

  void Node::Map::each_ref( const std::function<void(const Node*)>& fn ) const {
    _map.each_value(fn);
  }

  const Node::Result Node::Map::traverse( const std::string ) const {
    return Node::Result::fail;
  }

  Node* Node::Map::replace( Node* placeholder, Node* with ){
    _map.replace( placeholder, with );
    return this;
  }

  void Node::Map::setDefault( Node* node ){
    _map.set( symbol::MIN , symbol::MAX , node );
  }

}
