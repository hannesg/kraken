#ifndef KRAKEN_RANGE_MAP_H_
#define KRAKEN_RANGE_MAP_H_

#include <functional>
#include <iostream>
#include <stack>
namespace Kraken {

template<typename V>
struct overwrite : public std::binary_function<V,V,V>
{
  V operator()(V , V x){
    return x;
  } 
};


template< typename K, typename V>
class RangeMap;
}

#include "kraken/range_set.h"

namespace Kraken {
template< typename K, typename V>
class RangeMap {

  class Iterator;

  class Node {

  public:

    Node(K min, K max, V value);
    Node(const Node&);
    //Node(const Node*);
    ~Node();
    inline V value() const { return _value; };
    inline K min() const { return _min; };
    inline K max() const { return _max; };
    inline bool leave() const { return _left == nullptr && _right == nullptr; };

  private:
    K _min;
    K _max;
    V _value;
    Node* _left;
    Node* _right;

    static Node* _insert( Node* node,  K min, K max, V value, std::function<V(V,V)> merger);
    static void _each( Node* node, const std::function<void(const K&, const K&, const V&)>& fn );
    static void _each_value( Node* node, const std::function<void(const V&)>& fn );
    static void _replace( Node* node, const V x, const V with );

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
  RangeMap(const RangeMap<K,V>&);
  RangeMap(RangeMap<K,V>&&);
  virtual ~RangeMap();
  V operator[](const K& key) const;
  void set( K, K, V, std::function<V(V,V)> = overwrite<V>() );
  void set( K, V, std::function<V(V,V)> = overwrite<V>() );
  void set( const Kraken::RangeSet<K>&, V, std::function<V(V,V)> = overwrite<V>() );
  void each( const std::function<void(const K&, const K&, const V&)>& ) const;
  void each_value( const std::function<void(const V&)>& ) const;
  Iterator begin();
  inline Iterator end() const { return nullptr; };
  inline bool empty() const { return _node == nullptr; };
  inline bool singularity() const { return !empty() && _node->leave() && _node->min() == _node->max();};
  void replace( const V x, const V with );

protected:

//  static Node* RNMPInsert( Node* node,  K min, K max, V value, std::function<V(V,V)> merger );
//  static RangeMap<K,V,NIL>::Node* RNMPInsert2( RangeMapNode<K,V>* node, RangeMapNode<K,bool>* node2, V value, std::function<V(V,V)> merger );
  Node* _node;
  V _nil;
};

template< typename K, typename V  >
RangeMap<K,V>::Node::~Node(){
  if( _left != nullptr ) delete _left;
  if( _right != nullptr ) delete _right;
};


template< typename K, typename V >
RangeMap<K,V>::Node::Node(K min, K max, V value) : _min(min), _max(max), _value(value), _left(nullptr), _right(nullptr) {
};
/*
template< typename K, typename V>
RangeMap<K,V>::Node::Node(const RangeMap<K,V>::Node * node) : _min(node->_min), _max(node->_max), _value(node->_value), _left(nullptr), _right(nullptr) {
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
*/
template< typename K, typename V>
RangeMap<K,V>::Node::Node(const RangeMap<K,V>::Node &node) : _min(node._min), _max(node._max), _value(node._value), _left(nullptr), _right(nullptr) {
  if( node._left == nullptr ){
    _left = nullptr;
  }else{
    _left = new Node(*(node._left));
  }
  if( node._right == nullptr ){
    _right = nullptr;
  }else{
    _right = new Node(*(node._right));
  }
};

template< typename K, typename V>
RangeMap<K,V>::RangeMap() : _node(nullptr), _nil(0) {
};

template< typename K, typename V>
RangeMap<K,V>::RangeMap(const RangeMap<K,V> &rm) : _node(nullptr), _nil(rm._nil){
  if( rm._node != nullptr ){
    _node = new Node( *(rm._node) );
  }
};

template< typename K, typename V>
RangeMap<K,V>::RangeMap(RangeMap<K,V> &&rm) : _node(rm._node), _nil(rm._nil){
  rm._node = nullptr;
};

template< typename K, typename V>
RangeMap<K,V>::~RangeMap(){
  if( _node != nullptr ) delete _node;
};

template< typename K, typename V>
V RangeMap<K,V>::operator[]( const K& key) const{
  RangeMap<K,V>::Node* node = _node;
  while( node != nullptr ){
    if( key < node->_min ){
      node = node->_left;
    }else if( key > node->_max ){
      node = node->_right;
    }else{
      return node->_value;
    }
  }
  return _nil;
};

template< typename K, typename V>
typename RangeMap<K,V>::Node* RangeMap<K,V>::Node::_insert( Node* node, K min, K max, V value, std::function<V(V,V)> merger ){
  if( nullptr == node ){
    return new typename RangeMap<K,V>::Node( min, max, value);
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

template< typename K, typename V >
void RangeMap<K,V>::Node::_each( RangeMap<K,V>::Node *node, const std::function<void(const K&, const K&, const V&)>& fn ) {
  if( node == nullptr ){
    return ;
  }else{
    fn( node->min(), node->max(), node->value() );
    _each( node->_left, fn);
    _each( node->_right, fn);
  }
}

template< typename K, typename V >
void RangeMap<K,V>::Node::_each_value( RangeMap<K,V>::Node *node, const std::function<void(const V&)>& fn ) {
  if( node == nullptr ){
    return ;
  }else{
    fn( node->value() );
    _each_value( node->_left, fn);
    _each_value( node->_right, fn);
  }
}

template< typename K, typename V >
void RangeMap<K,V>::Node::_replace( RangeMap<K,V>::Node *node, const V x, const V with ) {
  if( node == nullptr ){
    return ;
  }else{
    if( x == node->value() ){
      node->_value = with;
    }
    _replace( node->_left, x, with);
    _replace( node->_right, x, with);
  }
}


template< typename K, typename V>
void RangeMap<K,V>::each( const std::function<void(const K&, const K&, const V&)>& fn ) const {
  RangeMap<K,V>::Node::_each( _node, fn );
}

template< typename K, typename V>
void RangeMap<K,V>::each_value( const std::function<void(const V&)>& fn ) const {
  RangeMap<K,V>::Node::_each_value( _node, fn );
}

template< typename K, typename V>
void RangeMap<K,V>::set( K min , K max, V value, std::function<V(V,V)> merger ){
  _node = Node::_insert( _node, min , max, value, merger );
}

template< typename K, typename V>
void RangeMap<K,V>::set( K mm , V value, std::function<V(V,V)> merger ){
  this->set(mm, mm, value, merger);
}

template< typename K, typename V>
void RangeMap<K,V>::set( const Kraken::RangeSet<K>& zet, V value, std::function<V(V,V)> merger ){
  zet.each( [value, merger, this]( const K &min, const K &max, const bool &cond ){
    if( cond ){
      this->set( min, max, value, merger );
    }
  });
}

template< typename K, typename V>
void RangeMap<K,V>::replace( const V x, const V with ){
  RangeMap<K,V>::Node::_replace( _node, x, with);
}

}
#endif
