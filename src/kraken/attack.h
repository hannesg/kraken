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

  public:
    inline Attack( const Kraken::The *kraken, const Kraken::Decoder& d, const char* const c) :
      _kraken(kraken), _head(nullptr), _decoder(d) {
        _head = new Link(c, Node::Result(kraken->root()));
        _head->acquire();
    }
    inline ~Attack(){
      _head->release();
    }
    inline bool step(){
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
    inline void attack(){
      bool go = true;
      while( true ){
        go = step();
        if( !go ) return ;
        if( found() ) return ;
      }
    }
    inline bool found() const{
      return _head->isSuccess();
    }
    inline const Link* head() const{
      return _head;
    }
    inline Link* head() {
      return _head;
    }

  };

}
#endif