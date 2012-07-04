#include "kraken/link.h"
namespace Kraken {
	Link::Link( Link* parent ) : _result(nullptr), _parent(parent), _refs(0) {
		if( _parent ){
			_parent->acquire();
		}
	}
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