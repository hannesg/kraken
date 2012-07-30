#ifndef KRAKEN_NODE_H
#define KRAKEN_NODE_H
#include "kraken/base.h"
#include "kraken/decoder.h"
#include <list>
#include <map>
#include <set>
#include <functional>
#include <string>
namespace Kraken {

  class Node{

  public:
    
    class Result;

    virtual void each_ref( const std::function<void(const Node*)>& ) const;
    virtual const Result traverse( const Kraken::Decoder& , const char* const ) const;
    virtual Node* replace( Node* placeholder, Node* with );
    virtual const std::function<const Node::Result(const Kraken::Decoder&, const char* const)> bindTraverse() const;
    virtual bool isTerminal() const;

    class Pool{
      std::list<Node*> _nodes;
    public:
      Pool& operator<<(Node*);
      void clear();
      void gc(Node* root);
      virtual ~Pool();
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
