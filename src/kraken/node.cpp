#include "kraken/node.h"
#include "kraken/visitor.h"
#include "kraken/node/gc.h"
#include <cstdio>
namespace Kraken {

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
 //       
        printf("Erase: node %p\n", *it);
        delete *it;
        _nodes.erase(it); 
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

  Node::~Node(){};

}
