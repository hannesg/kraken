#ifndef KRAKEN_LINK_H
#define KRAKEN_LINK_H
#include "kraken/decoder.h"
#include "kraken/node/result.h"
namespace Kraken {

	class Link;

	class Link {
		Node::Result _result;
		Link* _parent;
		const char* _string;
		volatile unsigned int _refs;
	public:
		Link(Link* const, const Node::Result&);
		Link(const char* string, const Node::Result&);
		~Link();
		inline Node::Result& result(){
			return _result;
		}
		void acquire();
		void release();

		Link* next(const Kraken::Decoder&);
	};

}
#endif