#include "kraken.h"
#include "kraken/node.h"
#include <memory>
#include <string>
namespace Kraken {

  class Attack {

    class Link {
      std::shared_ptr<Link> _previous;
      const Node *_node;
      size_t _offset;
      public:
      Link( const Node* node, size_t offset = 0, std::shared_ptr<Link> prev = nullptr );
    }

    std::shared_ptr<Kraken> _kraken;
    std::shared_ptr<Link> _head;
    const unsigned char *_string;

  public:
    Attack( Kraken *kraken, const unsigned char *string );

  };

}
