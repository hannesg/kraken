#include "kraken/attack.h"
namespace Kraken {

	Attack::Attack( const Kraken::The *kraken, const unsigned char *string ) : 
		_kraken(kraken), _head(nullptr), _string(string) {
		_head = new Link(Node::Result(kraken->root()));
	}

	bool Attack::step(){
		Link* head = _head;
		return head == nullptr;
	}

}