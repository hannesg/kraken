#ifndef KRAKEN_NODE_H
#define KRAKEN_NODE_H
#include <list>
#include <map>
#include <set>
#include <functional>
#include <string>
namespace Kraken {

  class Node{

  public:
    class Result {
      Node* _node;
      size_t _bytesize;
    public:
      Result( Node* );
      inline Node* node(){
        return _node;
      }
      inline size_t bytesize(){
        return _bytesize;
      }

    };

    class AltResult : public Result {

      AltResult* operator++();

    };

    class SimpleResult : public Result {

    };

    virtual void each_ref( const std::function<void(const Node*)>& ) const = 0;
    virtual const Result* traverse( const std::string ) const = 0;

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


  virtual ~Node();

  friend class Pool;

  class Map;

  };

};
#endif
