#include "kraken/node/terminal.h"
namespace Kraken {

Node::Terminal::Terminal( tentacle_id tentacle ) : _tentacle(tentacle) {
}

void Node::Terminal::each_ref( const std::function<void(const Node*)>& fn ) const {
  return ;
}

Node* Node::Terminal::replace( Node* placeholder, Node* with ){
  return this;
}

const Node::Result Node::Terminal::traverse( const std::string ) const {
  return Kraken::Node::Result::fail;
}

}
