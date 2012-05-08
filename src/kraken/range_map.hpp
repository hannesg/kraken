#ifndef KRAKEN_RANGE_MAP_H_
#define KRAKEN_RANGE_MAP_H_

#include <functional>
#include <iostream>
#include <stack>
namespace Kraken{

template<typename V>
struct overwrite : public std::binary_function<V,V,V>
{
  V operator()(V , V x){
    return x;
  } 
};


template< typename K, typename V, V NIL >
class RangeMap;

#include "kraken/range_set.hpp"

template< typename K, typename V, V NIL >
class RangeMap {

  class Iterator;

  class Node {

  public:

    Node(K min, K max, V value);
    Node(const Node&);
    Node(const Node*);
    ~Node();
    inline V value() const { return _value; };
    inline K min() const { return _min; };
    inline K max() const { return _max; };

  private:
    K _min;
    K _max;
    Node* _left;
    Node* _right;
    V _value;

    static Node* _insert( Node* node,  K min, K max, V value, std::function<V(V,V)> merger);
    static void _each( Node* node, std::function<void(const K&, const K&, const V&)> fn );

    friend class RangeMap;
    friend class Iterator;
  };

  class Iterator{
    std::stack<Node*> _stack;
    Node* _current;

    Iterator(Node* node) : _stack(), _current(node) {
    }

    Iterator& operator++(){
      if( _current != nullptr ){
        if( _current->_left != nullptr ){
          if( _current->right != nullptr ){
            _stack.push(_current);
          }
          _current = _current->_left;
        }else if( _current->right != nullptr ){
          _current = _current->right;
        }else if( !_stack.empty() ){
          _current = _stack.pop()->_right;
        }else{
          _current = nullptr;
        }
      }
      return *this;
    }

  };

public:

// static overwrite<V>* ow = new overwrite();

  RangeMap();
  RangeMap(const RangeMap<K,V,NIL>&);
  RangeMap(RangeMap<K,V,NIL>&&);
  virtual ~RangeMap();
  V operator[](const K& key) const;
  void set( K, K, V, std::function<V(V,V)> = overwrite<V>() );
  void set( K, V, std::function<V(V,V)> = overwrite<V>() );
  void set( RangeSet<K>&, V, std::function<V(V,V)> = overwrite<V>() );
  void each( std::function<void(const K&, const K&, const V&)> );
  Iterator begin();
  inline Iterator end() const { return nullptr; };

protected:

//  static Node* RNMPInsert( Node* node,  K min, K max, V value, std::function<V(V,V)> merger );
//  static RangeMap<K,V,NIL>::Node* RNMPInsert2( RangeMapNode<K,V>* node, RangeMapNode<K,bool>* node2, V value, std::function<V(V,V)> merger );
  Node* _node;
};

template< typename K, typename V , V NIL >
RangeMap<K,V,NIL>::Node::~Node(){
  if( _left != nullptr ) delete _left;
  if( _right != nullptr ) delete _right;
};


template< typename K, typename V, V NIL >
RangeMap<K,V,NIL>::Node::Node(K min, K max, V value) : _min(min), _max(max), _value(value), _left(nullptr), _right(nullptr) {
};

template< typename K, typename V, V NIL >
RangeMap<K,V,NIL>::Node::Node(const RangeMap<K,V,NIL>::Node * node) : _min(node->_min), _max(node->_max), _value(node->_value){
  std::cout << "Clone Node";
  if( node->_left == nullptr ){
    _left = nullptr;
  }else{
    _left = new Node(node->_left);
  }
  if( node->_right == nullptr ){
    _right = nullptr;
  }else{
    _right = new Node(node->_right);
  }
};

template< typename K, typename V, V NIL >
RangeMap<K,V,NIL>::Node::Node(const RangeMap<K,V,NIL>::Node &node) : _min(node._min), _max(node._max), _value(node._value){
  std::cout << "Clone Node";
  if( node._left == nullptr ){
    _left = nullptr;
  }else{
    _left = new Node(node._left);
  }
  if( node._right == nullptr ){
    _right = nullptr;
  }else{
    _right = new Node(node._right);
  }
};

template< typename K, typename V, V NIL >
RangeMap<K,V,NIL>::RangeMap() : _node(nullptr) {
};

template< typename K, typename V, V NIL >
RangeMap<K,V,NIL>::RangeMap(const RangeMap<K,V,NIL> &rm){
  if( rm._node == nullptr ){
    _node = nullptr;
  }else{
    _node = new Node(rm._node);
  }
};

template< typename K, typename V, V NIL >
RangeMap<K,V,NIL>::RangeMap(RangeMap<K,V,NIL> &&rm){
  if( rm._node == nullptr ){
    _node = nullptr;
  }else{
    _node = rm._node;
    rm._node = nullptr;
  }
};

template< typename K, typename V, V NIL >
RangeMap<K,V,NIL>::~RangeMap(){
  if( _node != nullptr ) delete _node;
};

template< typename K, typename V, V NIL >
V RangeMap<K,V,NIL>::operator[]( const K& key) const{
  RangeMap<K,V,NIL>::Node* node = _node;
  while( node != nullptr ){
    if( key < node->_min ){
      node = node->_left;
    }else if( key > node->_max ){
      node = node->_right;
    }else{
      return node->_value;
    }
  }
  return NIL;
};

template< typename K, typename V, V NIL >
typename RangeMap<K,V,NIL>::Node* RangeMap<K,V,NIL>::Node::_insert( Node* node, K min, K max, V value, std::function<V(V,V)> merger ){
  if( nullptr == node ){
    return new typename RangeMap<K,V,NIL>::Node( min, max, value);
  }else if( max < node->_min ){
    node->_left = _insert( node->_left, min, max, value, merger );
    return node;
  }else if( min > node->_max ){
    node->_right = _insert( node->_right, min, max, value, merger );
    return node;
  }else{
    if( min < node->_min ){
      node->_left = _insert( node->_left, min , node->_min - 1 , value, merger );
    }else if( min > node->_min ){
      node->_left = _insert( node->_left, node->_min, min - 1, node->_value, merger );
      node->_min = min;
    }
    if( max > node->_max ){
      node->_right = _insert( node->_right, node->_max + 1, max , value, merger );
    }else if( max < node->_max ){
      node->_right = _insert( node->_right, max + 1, node->_max , node->_value, merger );
      node->_max = max;
    }
    node->_value = merger(node->_value, value);
    return node; 
  }
}

template< typename K, typename V, V NIL >
void RangeMap<K,V,NIL>::Node::_each( RangeMap<K,V,NIL>::Node *node, std::function<void(const K&, const K&, const V&)> fn ){
  if( node == nullptr ){
    return ;
  }else{
    fn( node->min(), node->max(), node->value() );
    _each( node->_left, fn);
    _each( node->_right, fn);
  }
}

template< typename K, typename V, V NIL >
void RangeMap<K,V, NIL >::each( std::function<void(const K&, const K&, const V&)> fn ){
  RangeMap<K,V,NIL>::Node::_each( _node, fn );
}

template< typename K, typename V, V NIL >
void RangeMap<K,V, NIL >::set( K min , K max, V value, std::function<V(V,V)> merger ){
  _node = Node::_insert( _node, min , max, value, merger );
}

template< typename K, typename V, V NIL >
void RangeMap<K,V, NIL>::set( K mm , V value, std::function<V(V,V)> merger ){
  this->set(mm, mm, value, merger);
}

template< typename K, typename V, V NIL >
void RangeMap<K,V, NIL >::set( RangeSet<K>& set, V value, std::function<V(V,V)> merger ){
  set.each( [value, merger, this]( const K &min, const K &max, const V &cond ){
    if( cond ){
      this->set( min, max, value, merger );
    }
  });
}

}
#endif
