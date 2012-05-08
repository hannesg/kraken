#ifndef KRAKEN_NODE_H
#define KRAKEN_NODE_H
#include <vector>
#include <map>
#include <set>
#include <functional>
namespace Kraken {

  class Node{

  public:

    virtual void each_ref( const std::function<void(const Node*)>& ) const = 0;

    class GC;

    class Pool{
      std::vector<Node*> _nodes;
    public:
      Pool& operator<<(Node*);
      void clear();
      void gc(Node* root);
      template<typename T>
      T* make(){
        T* result = new T();
        _nodes.push_back(result);
        return result;
      };
    };


  virtual ~Node();

  friend class Pool;

  };

};
#endif
