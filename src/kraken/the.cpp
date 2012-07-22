#include "kraken/the.h"
namespace Kraken{

	The::The() : _pool(new Node::Pool()), _root(nullptr) {
	}

	The::The( Node::Pool* pool, Node* root) : _pool(pool), _root(root) {
	}
}