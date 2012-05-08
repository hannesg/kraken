#include "kraken/visitor.h"
#include <functional>

namespace Kraken{

  void Visitor::start( Node* node ){
    _queue.push_back(node);
    _seen.insert(node);
  }

  void Visitor::queue_unseen( const Node* node ){
    if( !_seen.insert(const_cast<Node*>(node)).second ){
      _queue.push_back(const_cast<Node*>(node));
    }
  }

  void Visitor::traverse(){
    auto lb = std::bind(&Visitor::queue_unseen, this, std::placeholders::_1);
    while( !_queue.empty() ){
      Node* current = _queue.front();
      if( !visit( current ) ){
        _queue.clear();
        return;
      }
      _queue.pop_front();
      current->each_ref( lb );
    }
  }

  bool Visitor::visit( Node *node ){
    return true;
  }

}
