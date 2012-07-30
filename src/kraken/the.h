#ifndef KRAKEN_THE_H
#define KRAKEN_THE_H

#include "kraken/node.h"

namespace Kraken {

    /**
     * my name is kraken - the kraken
     */
    class The{
        Node::Pool* _pool;
        Node *_root;
    public:
        The();
        The( Node::Pool* pool, Node* root );
        inline Node* root() const {
            return _root;
        }
        inline Node*& root(){
            return _root;
        }

    };

}

#endif