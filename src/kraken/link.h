#ifndef KRAKEN_LINK_H
#define KRAKEN_LINK_H
#include <atomic>
#include "kraken/node/result.h"
namespace Kraken {

	class Link;

	class Link {
		volatile unsigned int _refs;
		Link* _parent;
		Node::Result _result;
	public:
		Link(Link*);
		Link(Link*, const Node::Result&);
		explicit Link();
		Link(const Node::Result&);
		~Link();
		void acquire();
		void release();
	};

}
#endif