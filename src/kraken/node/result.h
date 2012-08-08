#ifndef KRAKEN_NODE_RESULT_H
#define KRAKEN_NODE_RESULT_H
#include "kraken/decoder.h"
#include "kraken/node.h"
#include <cstring>
#include <functional>
namespace Kraken {

  class Node::Result{
  public:
    enum TYPE { SUCCESS, CONTINUATION, FAIL, ERROR };

    typedef std::function<const Node::Result(const Kraken::Decoder&, const char* const)> fork_function ;
  private:
    TYPE _type;
    size_t _bytesize;
    std::string _error;
    Node* _next;
    fork_function _fork;
    // TODO: captures!

    Result( TYPE, size_t = 0, std::string = 0, Node* = nullptr, fork_function = fork_function() );

  public:
    // Found something:
    Result( Node* , size_t = 0);
    // Found something aaaaaaaaaand has an alternative:
    Result( Node* , const fork_function , size_t = 0);
    Result( Node* , Node* , size_t = 0);

    //TODO: Found nothing but has anothe place to look at ?!?:
    //Result( std::function<const Node::Result(std::string)> );
    
    // Error with description:
    Result( std::string );
    Result( const char* );

    static const Result& fail();
    static const Result& success();

    ~Result(){};
    inline const size_t bytesize() const{
      return _bytesize;
    }
    inline const std::string error() const{
      return _error;
    }
    inline const Node* next() const{
      return _next;
    }
    inline const fork_function fork() const{
      return _fork;
    }
    inline const bool hasFork() const {
      return _fork != nullptr;
    }
    inline const Result retry(const Kraken::Decoder& d, const char* const c){
      if( !hasFork() ){
        return fail();
      }
      return _fork(d,c);
    }
    inline const TYPE type() const{
      return _type;
    }
    inline const bool isFail() const{
      return _type == FAIL;
    }
    inline const bool isError() const{
      return _type == ERROR;
    }
    inline const bool isContinuation() const{
      return _type == CONTINUATION;
    }
    inline const bool isSuccess() const{
      return _type == SUCCESS;
    }
    inline const bool isDeadEnd() const {
      return _type != CONTINUATION;
    }
    inline operator bool() const{
      return _type == CONTINUATION;
    }
  };

}
#endif