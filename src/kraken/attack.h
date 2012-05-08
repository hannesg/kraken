#include "kraken.h"
#include "kraken/node.h"
#include <shared_ptr>
#include <string>
namespace Kraken {

  class Attack {

    class Link {
      std::shared_ptr<Link> _pred;
      const Node *_node;
      size_t _offset;
      public:
      Link( const Node* node, size_t offset = 0, Link* pred = nullptr );
    }

    Kraken * _kraken;
    std::shared_ptr<Link> _head;
    const unsigned char  *_string;

  public:
    Attack( Kraken *kraken, const unsigned char *string );

  };

}
