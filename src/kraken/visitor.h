#ifndef KRAKEN_NODE_GC_H
#define KRAKEN_NODE_GC_H

#include "kraken/node.h"
#include <set>
#include <list>

namespace Kraken{


class Visitor{

  std::set<Node*> _seen;
  std::list<Node*> _queue;

private:
  void queue_unseen( const Node *node );

public:

  void start( Node *node );
  void traverse();
  virtual bool visit( Node *node );
  inline const std::set<Node*>& seen() const {
    return _seen;
  }
  inline bool seen( const Node* node ) const {
    return _seen.find( const_cast<Node*>(node) ) != _seen.end();
  }

};


}
#endif
