#include "kraken/link.h"
namespace Kraken {
	Link::Link( Link* parent ) : _result(nullptr), _parent(parent), _refs(0) {
		_parent->acquire();
	}
	Link::Link( Link* parent, const Node::Result& result ) : _result(result), _parent(parent), _refs(0) {
		_parent->acquire();
	}
	Link::Link() : _result(nullptr), _parent(nullptr), _refs(0)  {}
	Link::Link( const Node::Result& result ) : _result(result), _parent(nullptr),_refs(0) {}
	Link::~Link() {
		if( _parent ){
			_parent->release();
		}
	}
	void Link::acquire(){
		_refs++;
	}
	void Link::release(){
		if( _refs-- == 0 ){
			delete this;
		}
	}
}