#include "kraken/node/result.h"
#include "kraken/node/map.h"
namespace Kraken {

  void Node::Map::each_ref( const std::function<void(const Node*)>& fn ) const {
    _map.each_value(fn);
  }

  const Node::Result Node::Map::traverse(const Kraken::Decoder& d, const char* const c) const {
    element r = d.read(c);
    if( r._error ) return "Invalid character";
    Node* node = _map[r._sym];
    return Node::Result(node, r._size);
  }

  Node* Node::Map::replace( Node* placeholder, Node* with ){
    _map.replace( placeholder, with );
    return this;
  }

}
