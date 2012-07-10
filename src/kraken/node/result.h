#ifndef KRAKEN_NODE_RESULT_H
#define KRAKEN_NODE_RESULT_H
#include "kraken/node.h"
#include <cstring>
#include <functional>
namespace Kraken {

 	class Node::Result{
 	public:
 		enum TYPE { SUCCESS, FAIL, ERROR };
    static const Result fail;
 	private:
    TYPE _type;
    size_t _bytesize;
    std::string _error;
    Node* _next;
    std::function<const Node::Result(std::string)> _fork;
    // TODO: captures!
  public:
    // Found something:
    Result( Node* , size_t = 0);
    // Found something aaaaaaaaaand has an alternative:
    Result( Node* , std::function<const Node::Result(std::string)> , size_t = 0);

    //TODO: Found nothing but has anothe place to look at ?!?:
    //Result( std::function<const Node::Result(std::string)> );
    
    // Error with description:
    Result( std::string );
    Result( const char* );
    
    // Didn't find anything:
    Result( std::nullptr_t );

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
    inline const std::function<const Node::Result(std::string)> fork() const{
      return _fork;
    }
    inline const bool hasFork() const {
      return _fork != nullptr;
    }
    inline const Result retry(std::string s){
      return _fork(s);
    }
    inline const bool isFail() const{
      return _type == FAIL;
    }
    inline const bool isError() const{
      return _type == ERROR;
    }
    inline const bool isSuccess() const{
      return _type == SUCCESS;
    }
    inline operator bool() const{
      return _type == SUCCESS;
    }
  };

}
#endif