#ifndef KRAKEN_NODE_PLACEHOLDER_H
#define KRAKEN_NODE_PLACEHOLDER_H
#include "kraken/node.h"
#include "kraken/node/result.h"

namespace Kraken {

  class Node::Placeholder : public Node {
    virtual void each_ref( const std::function<void(const Node*)>& ) const;
    virtual const Node::Result traverse( const std::string ) const;
    virtual Node* replace( Node* placeholder, Node* with );
  };

}

#endif
