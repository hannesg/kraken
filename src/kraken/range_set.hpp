#ifndef KRAKEN_RANGE_SET_H_
#define KRAKEN_RANGE_SET_H_
#include "kraken/range_map.hpp"

namespace {

template< typename K >
class RangeSet : public RangeMap<K, bool, false>{

void add( K mm , std::function<bool(bool,bool)> merger = overwrite<bool>() ){
  set( mm, true , merger );
}
void add( K min, K max , std::function<bool(bool,bool)> merger = overwrite<bool>() ){
  set( min, max , true , merger );
}

RangeSet<K> operator+( RangeSet<K> s){
  
}

};

}

#endif
