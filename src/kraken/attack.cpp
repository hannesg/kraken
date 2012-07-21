#include "kraken/attack.h"
namespace Kraken {

	Attack::Attack( const Kraken::The *kraken, const Kraken::Decoder& d, const char* const c ) : 
		_kraken(kraken), _head(nullptr), _decoder(d), _string(c) {
		_head = new Link(Node::Result(kraken->root()));
	}

	bool Attack::step(){
		Link* head = _head;
		return head == nullptr;
	}

}