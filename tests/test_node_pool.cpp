
#include "kraken/node.h"
#include "kraken/node/map.h"
#include "kraken/node/terminal.h"
#include "kraken/node/result.h"
#include "kraken/base.h"
#include <functional>
#include <algorithm>
#include <list>

class RealNode : public Kraken::Node {

std::list<Kraken::Node*> _nodes;

public:
  virtual void each_ref( const std::function<void(const Kraken::Node*)>& ) const;
  virtual const Kraken::Node::Result traverse( const Kraken::string ) const;
  RealNode* add(Kraken::Node* node);
  ~RealNode();

};

void RealNode::each_ref( const std::function<void(const Kraken::Node*)>& fn ) const {
  std::for_each( _nodes.begin(), _nodes.end(), fn);
  return ;
}

const Kraken::Node::Result RealNode::traverse( const Kraken::string ) const {
  return Kraken::Node::Result::fail;
}

RealNode::~RealNode(){
  _nodes.clear();
}

RealNode* RealNode::add(Kraken::Node* node){
  _nodes.push_back(node);
  return this;
}

int main(int argc, char** argv){


  Kraken::Node::Pool *pool = new Kraken::Node::Pool();
  RealNode *node = pool->make<RealNode>();
  Kraken::Node::Map *map = pool->make<Kraken::Node::Map>();
  node->add( pool->make<RealNode>() )->add( pool->make<RealNode>() );
  node->add( map );
  map->set( 10, 20 , pool->make<RealNode>() );
  map->set( 10, 20 , pool->make<RealNode>() );
  map->set( 15, 25 , pool->make<RealNode>() );
  map->set( 26, 28 , pool->make<Kraken::Node::Terminal>(0) );
  pool->make<RealNode>();
  pool->make<RealNode>();
  pool->make<Kraken::Node::Map>()->set(10,15, pool->make<RealNode>());

  pool->gc( node );

  pool->clear();
  delete pool;

}
