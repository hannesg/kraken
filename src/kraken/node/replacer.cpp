#include "kraken/node/replacer.h"
namespace Kraken {

  Replacer::Replacer( Node* old, Node* nu ) : _old(old), _new(nu) {

  }

  bool Replacer::visit( Node* node ){
    node->replace(_old, _new);
    return true;
  }

}
