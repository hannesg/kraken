#ifndef KRAKEN_NODE_MAP_H
#define KRAKEN_NODE_MAP_H
#include "kraken/base.h"
#include "kraken/node.h"
#include "kraken/range_map.h"
#include "kraken/range_set.h"
namespace Kraken{

  class Node::Map : public Node{
    RangeMap<symbol,Node*> _map;
    public:
    virtual void each_ref( const std::function<void(const Node*)>& ) const;
    virtual const Node::Result traverse( const Kraken::string ) const;
    virtual Node* replace( Node* placeholder, Node* with );
    template<typename... T>
      inline void set( T... args ){
        _map.set(args...);
      }
    //void set( symbol, symbol, Node* );
    //void set( RangeSet<symbol>&, Node* );
  };

}
#endif
