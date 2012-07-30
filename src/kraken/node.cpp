#include "kraken/node.h"
#include "kraken/visitor.h"
#include <functional>
namespace Kraken {

  void Node::each_ref( const std::function<void(const Node*)>& ) const {
    return;
  }

  Node* Node::replace( Node* placeholder, Node* with ){
    return this;
  }

  const Node::Result Node::traverse( const Kraken::Decoder&, const char* const ) const {
    return Kraken::Node::Result::fail;
  }

  const std::function<const Node::Result(const Kraken::Decoder&, const char* const)> Node::bindTraverse() const {
    return std::bind( &Node::traverse, this, std::placeholders::_1, std::placeholders::_2 );
  }

  Node::Pool& Node::Pool::operator<<(Node* node){
    _nodes.push_back(node);
    return *this;
  }

  bool Node::isTerminal() const {
    return false;
  }

  void Node::Pool::gc(Node* root){
    Visitor vs;
    vs.start( root );
    vs.traverse();
    // vs now contains all live nodes
    for( auto it =  _nodes.begin() ; it != _nodes.end() ; ){
      if( !vs.seen( *it ) ){
        auto temp = it;
        temp++;
        delete *it;
        _nodes.erase(it);
        it = temp;
      }else{
        it++;
      }
    }
  }

  Node::Pool::~Pool(){
    clear();
  }

  void Node::Pool::clear(){
    for( auto it =  _nodes.begin() ; it != _nodes.end() ; it++ ){
      delete *it;
    }
    _nodes.clear();
  }

}
