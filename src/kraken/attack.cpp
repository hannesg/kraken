#include "kraken/attack.h"
namespace Kraken {

	Attack::Attack( const Kraken::The *kraken, const Kraken::Decoder& d, const char* const c ) : 
		_kraken(kraken), _head(nullptr), _decoder(d) {
		_head = new Link(c, Node::Result(kraken->root()));
		_head->acquire();
	}

	bool Attack::step(){
		Link* nxt = _head->next(_decoder);
		if( nxt ){
			nxt->acquire();
			_head->release();
			_head = nxt;
			return true;
		}else{
			return false;
		}
	}

}