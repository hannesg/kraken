#ifndef KRAKEN_NODE_PLACEHOLDER_H
#define KRAKEN_NODE_PLACEHOLDER_H
#include "kraken/node.h"
#include "kraken/node/result.h"

namespace Kraken {

  class Node::Placeholder : public Node {
    virtual const Node::Result traverse( const Kraken::Decoder&, const char* const ) const;
  };

}

#endif
