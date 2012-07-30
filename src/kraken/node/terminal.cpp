#include "kraken/node/terminal.h"
namespace Kraken {

Node::Terminal::Terminal( tentacle_id tentacle ) : _tentacle(tentacle) {
}

bool Node::Terminal::isTerminal() const {
  return true;
}

tentacle_id Node::Terminal::endingTentacle() const {
  return _tentacle;
}


}
