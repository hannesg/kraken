#include "kraken/token.h"
#include "kraken/base.h"
#include "kraken/node/map.h"
#include "kraken/node/placeholder.h"
#include "kraken/node/replacer.h"
#include <sstream>
namespace Kraken {

Token::Token(unsigned int q ) : _min(q), _max(q) {};
Token::Token(unsigned int mi, unsigned int ma) : _min(mi), _max(ma) {}; 
Token::~Token(){};

Token* Token::at_least(unsigned int q){
  _min = q;
  return this;
}
Token* Token::at_most(unsigned int q){
  _max = q;
  return this;
}
Token* Token::unlimited(){
  _max = Token::_unlimited;
  return this;
}
Token* Token::optionally(){
  _min = 0;
  return this;
}

std::string Token::inspect_repetition() const{
  if( max() == 1 ){
    if( min() == 1 ){
      return "";
    }else if( min() == 0 ){
      return "?"; 
    }
  }else if( max() == _unlimited ){
    if( min() == 0 ){
      return "*";
    }else if( min() == 1 ){
      return "+";
    }
  }
  std::stringstream result;
  result << "{";
  if( min() > 0 ){
    result << min();
  }
  if( min() != max() ){
    result << ",";
    if( max() != _unlimited ){
      result << max();
    }
  }
  result << "}";
  return result.str();
}

Node* Token::toNode( Node::Pool& pool , Node* pred ) const {
  unsigned int mi = min();
  unsigned int ma = max();
  Node* result = pred;
  if( ma == Token::_unlimited ){
    result = toNodeSelfreferential( pool );
  }else if( ma > mi ){
    while( ma > mi ){
      result = toNodeOptional( pool, result );
      ma--;
    }
  }
  if( mi > 0 ){
    while( mi > 0 ){
      result = toNodeOnce( pool, result );
      mi--;
    }
  }
  return result;
}


Node* Token::toNodeSelfreferential( Node::Pool& pool ) const {
  Node* placeholder = pool.make<Node::Placeholder>();
  Node* result = toNodeOptional( pool, placeholder);
/*
  EHHMM, will this happen?
  if( result == placeholder ){
    return 
  }*/
  Replacer replacer = Replacer( placeholder, result );
  replacer.start(result);
  replacer.traverse();
  return result;
}

Token::Container::Container( std::initializer_list<Token*> lst, unsigned int q ) : Token(q), _tokens(lst) {}
Token::Container::Container( std::initializer_list<Token*> lst, unsigned int mi, unsigned int ma ) : Token(mi,ma), _tokens(lst) {}
Token::Container::~Container(){
  for( Token* tk : tokens() ){
    delete tk;
  }
}
Token::Alt::Alt( std::initializer_list<Token*> lst, unsigned int q ) : Token::Container::Container(lst, q) {}
Token::Alt::Alt( std::initializer_list<Token*> lst, unsigned int mi, unsigned int ma  ) : Token::Container::Container(lst, mi, ma) {}
Token::Seq::Seq( std::initializer_list<Token*> lst, unsigned int q ) : Token::Container::Container(lst, q) {}
Token::Seq::Seq( std::initializer_list<Token*> lst, unsigned int mi, unsigned int ma  ) : Token::Container::Container(lst, mi, ma) {}


Token::Group::Group( symbol s, unsigned int i ) : Token(i) {
  _map.add( s );
}

Token::Group::Group( symbol s, unsigned int mi, unsigned int ma ) : Token(mi,ma){
  _map.add( s );
}

Token::Group::Group( std::initializer_list<Kraken::RangeSet<symbol>> lst, unsigned int i ) : Token(i) {
  for( auto set : lst ){
    _map.add( set );
  }
}

Token::Group::Group( std::initializer_list<Kraken::RangeSet<symbol>> lst, unsigned int mi, unsigned int ma ) : Token(mi, ma) {
  for( auto set : lst ){
    _map.add( set );
  }
}

std::string Token::Seq::inspect() const{
  std::string result;
  for( Token *tk : tokens() ){
    result += tk->inspect();
  }
  result += inspect_repetition();
  return result;
}

std::string Token::Alt::inspect() const{
  std::string result;
  for( Token *tk : tokens() ){
    if( result.length() == 0 ){
      result += "(";
    }else{
      result += "|";
    }
    result += tk->inspect();
  }
  result += ")";
  result += inspect_repetition();
  return result;
}

std::string Token::Group::inspect() const{
  std::string result;
  if( !_map.singularity() ){
    result += '[';
  }
  _map.each([&result](const symbol lo, const symbol hi, bool){
    result += lo;
    if( lo != hi ){
      result += '-';
      result += hi;
    }
  });
  if( !_map.singularity() ){
    result += ']';
  }
  result += inspect_repetition();
  return result;
}

Node* Token::Seq::toNodeOnce( Node::Pool& pool , Node* pred ) const {
  Node* result = pred;
  for( auto it = tokens().rbegin(); it != tokens().rend(); it++ ){
    result = (*it)->toNodeOnce( pool, result );
  }
  return result;
}

Node* Token::Seq::toNodeSelfreferential( Node::Pool& pool) const {
  Node* placeholder = pool.make<Node::Placeholder>();
  Node* result = placeholder;
  /*;
  EHHMM, will this happen?
  if( result == placeholder ){
    return 
  }*/
  for( auto it = tokens().rbegin(); it != tokens().rend(); it++ ){
    result = (*it)->toNodeOnce( pool, result );
  }
  Replacer replacer = Replacer( placeholder, result );
  replacer.start(result);
  replacer.traverse();
  return result;
}

Node* Token::Seq::toNodeOptional( Node::Pool& pool, Node* yes) const {
  Node* result = yes;
  for( auto it = tokens().rbegin(); it != tokens().rend(); it++ ){
    result = (*it)->toNodeOptional( pool, result );
  }
  return result;
}


Node* Token::Alt::toNodeOnce( Node::Pool& pool , Node* pred ) const {
  Node::Map* result = pool.make<Node::Map>();
  return result;
}

Node* Token::Alt::toNodeSelfreferential( Node::Pool& pool ) const {
  Node::Map* result = pool.make<Node::Map>();
  return result;
}

Node* Token::Alt::toNodeOptional( Node::Pool& pool, Node* yes ) const {
  Node::Map* result = pool.make<Node::Map>();
  return result;
}

Node* Token::Group::toNodeOnce( Node::Pool& pool , Node* pred ) const {
  Node::Map* result = pool.make<Node::Map>();
  result->set( _map, pred );
  return result;
}

Node* Token::Group::toNodeSelfreferential( Node::Pool& pool ) const {
  Node::Map* result = pool.make<Node::Map>();
  result->set( _map, result );
  return result;
}

Node* Token::Group::toNodeOptional( Node::Pool& pool, Node* yes ) const {
  Node::Map* result = pool.make<Node::Map>();
  result->set( _map, yes );
  return result;
}

}
