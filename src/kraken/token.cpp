#include "kraken/token.h"
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

Token::Container::Container( std::initializer_list<Token*> lst, unsigned int q ) : _tokens(lst), Token(q) {}
Token::Container::Container( std::initializer_list<Token*> lst, unsigned int mi, unsigned int ma ) : _tokens(lst), Token(mi,ma) {}
Token::Container::~Container(){
  for( Token* tk : _tokens ){
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

std::string Token::Seq::inspect(){
  std::string result;
  for( Token *tk : tokens() ){
    result += tk->inspect();
  }
  result += inspect_repetition();
  return result;
}

std::string Token::Alt::inspect(){
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

std::string Token::Group::inspect(){
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

}
