#ifndef KRAKEN_NODE_REPLACER_H
#define KRAKEN_NODE_REPLACER_H

#include "kraken/visitor.h"
#include "kraken/node.h"

namespace Kraken {

  class Replacer : public Visitor {
    Node* _old;
    Node* _new;
  public:
    Replacer( Node*, Node*);
    bool visit( Node *node );
    ~Replacer() {};

  };

}

#endif
