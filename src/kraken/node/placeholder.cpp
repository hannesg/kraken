#include "kraken/node/placeholder.h"
#include <iostream>
namespace Kraken {

const Node::Result Node::Placeholder::traverse( const Kraken::Decoder&, const char* const ) const {
  return "Traversing a placeholder node. This is definitely an error.";
}

}
