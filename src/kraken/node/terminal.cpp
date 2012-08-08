#include "kraken/node/terminal.h"
namespace Kraken {

Node::Terminal::Terminal( tentacle_id tentacle ) : _tentacle(tentacle) {
}

const Node::Result Node::Terminal::traverse( const Kraken::Decoder& , const char* const ) const {
  return Node::Result::success();
}

}
