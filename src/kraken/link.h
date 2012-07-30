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
		inline const Node::Result& result() const{
			return _result;
		}
		inline Node::Result& result(){
			return _result;
		}
		inline bool isTerminal() const{
			return _result.isTerminal();
		}
		void acquire();
		void release();

		Link* next(const Kraken::Decoder&);
	};

}
#endif