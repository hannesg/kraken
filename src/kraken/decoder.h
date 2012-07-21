#ifndef KRAKEN_DECODER_H
#define KRAKEN_DECODER_H

#include "kraken/base.h"

namespace Kraken{

	class Decoder {

	public:
		virtual const element read(const char* const) const = 0;
		virtual ~Decoder(){};

	};

}

#endif