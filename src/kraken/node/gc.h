#ifndef KRAKEN_NODE_GC_H
#define KRAKEN_NODE_GC_H

#include "kraken/node.h"
#include "kraken/visitor.h"
#include <set>
#include <queue>

namespace Kraken{


class Node::GC : public Visitor {

  public:

  GC( Kraken::Node::Pool *pool );
  void visit( Kraken::Node *node );

};


}
#endif
