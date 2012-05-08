
#include "kraken/node.h"
#include <functional>
#include <algorithm>
#include <list>

class RealNode : public Kraken::Node {

std::list<Kraken::Node*> _nodes;

public:
  virtual void each_ref( const std::function<void(const Kraken::Node*)>& ) const;
  RealNode* add(Kraken::Node* node);
  ~RealNode();

};

void RealNode::each_ref( const std::function<void(const Kraken::Node*)>& fn ) const {
  std::for_each( _nodes.begin(), _nodes.end(), fn);
  return ;
}

RealNode::~RealNode(){
  printf("clearing RealNode\n");
  _nodes.clear();
}

RealNode* RealNode::add(Kraken::Node* node){
  _nodes.push_back(node);
  return this;
}

int main(int argc, char** argv){


  Kraken::Node::Pool *pool = new Kraken::Node::Pool();
  RealNode *node = pool->make<RealNode>();
  node->add( pool->make<RealNode>() )->add( pool->make<RealNode>() );
  pool->make<RealNode>();
  pool->make<RealNode>();
//  pool->gc( node );

  pool->clear();
  delete pool;

}
