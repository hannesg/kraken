#ifndef KRAKEN_ATTACK_H
#define KRAKEN_ATTACK_H
#include "kraken.h"
#include "kraken/node.h"
#include "kraken/link.h"
#include "kraken/the.h"
#include <string>
namespace Kraken {

  class Attack {

    const Kraken::The *_kraken;
    Link* _head;
    const Kraken::Decoder& _decoder;
    const char* const _string;

  public:
    Attack( const Kraken::The *kraken, const Kraken::Decoder& d, const char* const c);
    bool step();

  };

}
#endif