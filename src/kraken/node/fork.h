#ifndef KRAKEN_NODE_FORK_H
#define KRAKEN_NODE_FORK_H
#include "kraken/node.h"
namespace Kraken {

    class Node::Fork : public Node{
        Node* _main;
        Node* _fork;
    public:
        virtual void each_ref( const std::function<void(const Node*)>& ) const;
        virtual const Node::Result traverse( const Kraken::string ) const;
        virtual Node* replace( Node* placeholder, Node* with );
    };


}
#endif