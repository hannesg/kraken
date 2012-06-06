#include "kraken/node/map.h"
namespace Kraken {

  void Node::Map::each_ref( const std::function<void(const Node*)>& fn ) const {
    _map.each_value(fn);
  }

  const Node::Result* Node::Map::traverse( const std::string ) const {
    return nullptr;
  }

}
