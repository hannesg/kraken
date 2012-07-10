#include "kraken/node.h"
#include "kraken/visitor.h"
#include <cstdio>
#include <functional>
namespace Kraken {

  void Node::each_ref( const std::function<void(const Node*)>& ) const {
    return;
  }

  Node* Node::replace( Node* placeholder, Node* with ){
    return this;
  }

  const std::function<const Node::Result(Kraken::string)> Node::bindTraverse() const {
    return std::bind( &Node::traverse, this, std::placeholders::_1 );
  }

  Node::Pool& Node::Pool::operator<<(Node* node){
    _nodes.push_back(node);
    return *this;
  }

  void Node::Pool::gc(Node* root){
    Visitor vs;
    vs.start( root );
    vs.traverse();
    // vs now contains all live nodes
    for( auto it =  _nodes.begin() ; it != _nodes.end() ; ){
      if( !vs.seen( *it ) ){
        auto temp = it;
        printf("Erase: node %p\n", *it);
        temp++;
        delete *it;
        _nodes.erase(it);
        it = temp;
      }else{
        printf("Keep: node %p\n", *it);
        it++;
      }
    }
  }

  void Node::Pool::clear(){
    for( auto it =  _nodes.begin() ; it != _nodes.end() ; it++ ){
      printf("Clear node %p\n", *it);
      delete *it;
    }
    _nodes.clear();
  }

}
