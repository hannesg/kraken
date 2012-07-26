#include "kraken/token.h"
#include "kraken/node.h"
#include "kraken/node/terminal.h"
#include <cstdio>
int main(int argc, char** argv){

  Kraken::Token *t = new Kraken::Token::Alt({
    new Kraken::Token::Group('a', 0,1),
    new Kraken::Token::Group('$'),
    new Kraken::Token::Group(0),
    new Kraken::Token::Group(0x100, 10,1000),
    (new Kraken::Token::Group(0x10000))->optionally()->unlimited(),
    new Kraken::Token::Group( {Kraken::RangeSet<Kraken::symbol>(0x100,0x200), Kraken::RangeSet<Kraken::symbol>(0x300,0x400)} )
  });

  std::cout << t->inspect();

  Kraken::Node::Pool pool;

  Kraken::Node* terminal = pool.make<Kraken::Node::Terminal>(0);
  Kraken::Node* node = t->toNode(pool, terminal);


  delete t;

  return 0;
}
