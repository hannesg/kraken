#include "kraken/node/placeholder.h"
#include <iostream>
namespace Kraken {

void Node::Placeholder::each_ref( const std::function<void(const Node*)>& fn ) const {
  return ;
}

Node* Node::Placeholder::replace( Node* placeholder, Node* with ){
  return this;
}

const Node::Result Node::Placeholder::traverse( const std::string ) const {
  std::cerr << "Traversing a placeholder node. This is definitely an error.";
  return Kraken::Node::Result::fail;
}

}
