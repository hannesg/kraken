#ifndef KRAKEN_THE_H
#define KRAKEN_THE_H

#include "kraken/node.h"

namespace Kraken {
	class The;
}

#include "kraken/attack.h"

namespace Kraken {

	/**
	 * my name is kraken - the kraken
	 */
	class The{
    	Node::Pool _pool;
    	Node *_root;
    public:
    	The();
    	template<typename T, typename... Args>
    	The(Args... args) : _pool(), _root(nullptr) {
	        _root = _pool.make<T>( args... );
	    };
//    	Attack* attack( Kraken::string ) const;
    	inline Node* root() const {
    		return _root;
    	}

	};

}

#endif