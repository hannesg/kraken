#ifndef KRAKEN_NODE_H
#define KRAKEN_NODE_H
#include "kraken/base.h"
#include <list>
#include <map>
#include <set>
#include <functional>
#include <string>
namespace Kraken {

  class Node{

  public:
    
    class Result;

    virtual void each_ref( const std::function<void(const Node*)>& ) const = 0;
    virtual const Result traverse( const std::string ) const = 0;
    virtual Node* replace( Node* placeholder, Node* with ) = 0;
    virtual const std::function<const Node::Result(Kraken::string)> bindTraverse() const;

    class Pool{
      std::list<Node*> _nodes;
    public:
      Pool& operator<<(Node*);
      void clear();
      void gc(Node* root);
      template<typename T, typename... Args>
      T* make(Args... args){
        T* result = new T( args... );
        _nodes.push_back(result);
        return result;
      };
    };

    virtual ~Node(){};

    friend class Pool;

    class Map;
    class Terminal;
    class Placeholder;
    class Fork;

  };

};

#include "kraken/node/result.h"

#endif
