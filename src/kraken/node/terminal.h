#ifndef KRAKEN_NODE_TERMINAL_H
#define KRAKEN_NODE_TERMINAL_H
#include "kraken/node.h"
#include "kraken/base.h"
#include "kraken/node/result.h"

namespace Kraken {

  class Node::Terminal : public Node {
    tentacle_id _tentacle;
  public:
    Terminal(tentacle_id);
    virtual void each_ref( const std::function<void(const Node*)>& ) const;
    virtual const Node::Result traverse( const Kraken::string ) const;
    virtual Node* replace( Node* placeholder, Node* with );
  };

}

#endif
