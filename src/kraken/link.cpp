#include "kraken/link.h"
namespace Kraken {
	Link::Link( Link* const parent, const Node::Result& result ) :
		_result(result),
		_parent(parent),
		_string(parent->_string + result.bytesize()),
		_refs(0) {
		_parent->acquire();
	}
	Link::Link( const char* const str, const Node::Result& result ) :
		_result(result),
		_parent(nullptr),
		_string(str),
		_refs(0)
		{

		};
	Link::~Link() {
		if( _parent ){
			_parent->release();
		}
	}
	void Link::acquire(){
		_refs++;
	}
	void Link::release(){
		if( _refs-- == 1 ){
			delete this;
		}
	}

	Link* Link::next(const Kraken::Decoder& dec){
		const Node* next = result().next();
		const Node::Result result = next->traverse(dec, _string);
		if( result.isFail() ){
			// try backtrace
			
			return nullptr;
		}else{
			return new Link( this, result );
		}
	}
}