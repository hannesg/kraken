#ifndef KRAKEN_TOKEN_H
#define KRAKEN_TOKEN_H

#include <list>
#include <string>
#include <climits>
#include "kraken/base.h"
#include "kraken/range_map.h"
#include "kraken/node.h"
#include "kraken/node/replacer.h"
namespace Kraken {

  class Token {

    unsigned int _min;
    unsigned int _max;

    inline void min(unsigned int i){
      _min = i;
    }

    inline void max(unsigned int i){
      _max = i;
    }

  protected:
    std::string inspect_repetition() const;

  public:

    static const unsigned int _unlimited = UINT_MAX;

    inline const unsigned int min() const{
      return _min;
    }

    inline const unsigned int max() const{
      return _max;
    }

    Token(unsigned int q = 1);
    Token(unsigned int mi, unsigned int ma);

    virtual ~Token();

    virtual std::string inspect() const = 0;
    virtual Node* toNode( Node::Pool& , Node* pred ) const ;
    virtual Node* toNodeOnce( Node::Pool& , Node* pred ) const = 0;
    virtual Node* toNodeSelfreferential( Node::Pool& ) const ;
    virtual Node* toNodeOptional( Node::Pool&, Node* ) const = 0;

    Token* at_least(unsigned int q);
    Token* at_most(unsigned int q);
    Token* unlimited();
    Token* optionally();

    class Container;
    class Seq;
    class Alt;
    class Group;

  };

    class Token::Container : public Token { 
      std::list<Token*> _tokens;
    public:
      inline const std::list<Token*>& tokens() const{
        return _tokens;
      }
      Container( std::initializer_list<Token*>, unsigned int = 1);
      Container( std::initializer_list<Token*>, unsigned int , unsigned int );
      ~Container();
    };

    class Token::Seq : public Token::Container {
    public:
      std::string inspect() const;
      virtual Node* toNodeOnce( Node::Pool&, Node* ) const;
      virtual Node* toNodeSelfreferential( Node::Pool& ) const;
      virtual Node* toNodeOptional( Node::Pool&, Node*) const;
      Seq( std::initializer_list<Token*>, unsigned int = 1);
      Seq( std::initializer_list<Token*>, unsigned int , unsigned int );
    };

    class Token::Alt : public Token::Container {
    public:
      std::string inspect() const;
      virtual Node* toNodeOnce( Node::Pool& , Node* pred ) const;
      virtual Node* toNodeSelfreferential( Node::Pool& ) const;
      virtual Node* toNodeOptional( Node::Pool&, Node* ) const;
      Alt( std::initializer_list<Token*>, unsigned int = 1);
      Alt( std::initializer_list<Token*>, unsigned int , unsigned int );
    };

    class Token::Group : public Token {
      Kraken::RangeSet<symbol> _map;
    public:
      std::string inspect() const;
      virtual Node* toNodeOnce( Node::Pool& , Node* pred ) const;
      virtual Node* toNodeSelfreferential( Node::Pool& ) const;
      virtual Node* toNodeOptional( Node::Pool&, Node* ) const;
      Group(symbol, unsigned int = 1);
      Group(symbol, unsigned int , unsigned int);
      Group( std::initializer_list<Kraken::RangeSet<symbol>>, unsigned int = 1 );
      Group( std::initializer_list<Kraken::RangeSet<symbol>>, unsigned int, unsigned int );
    };

}

#endif
