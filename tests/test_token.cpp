#include "kraken/token.h"
#include <cstdio>
int main(int argc, char** argv){

  Kraken::Token *t = new Kraken::Token::Alt({
    new Kraken::Token::Group('a', 0,1),
    new Kraken::Token::Group('$'),
    new Kraken::Token::Group(0),
    new Kraken::Token::Group(0x100, 10,1000),
    (new Kraken::Token::Group(0x10000))->optionally()->unlimited()
  });

  std::cout << t->inspect();

  delete t;

  return 0;
}
