#include "kraken/node/fork.h"
#include "kraken/node/result.h"
namespace Kraken {

void Node::Fork::each_ref( const std::function<void(const Node*)>& fun ) const {
	fun(_main);
	if( _fork ) fun(_fork);
};

const Node::Result Node::Fork::traverse( const Kraken::string ) const {
	if( _fork ){
		return Node::Result( _main, _fork->bindTraverse() );
	}else{
		return _main;
	}
};

Node* Node::Fork::replace( Node* placeholder, Node* with ){
	if( _main == placeholder ){
		_main = placeholder;
	}
	if( _fork == placeholder ){
		_fork = placeholder;
	}
	return this;
};

}
