#ifndef KRAKEN_RANGE_SET_H_
#define KRAKEN_RANGE_SET_H_
#include "kraken/range_map.h"

namespace Kraken {

template< typename K >
class RangeSet : public RangeMap<K, bool>{
  public:
void add( K mm , std::function<bool(bool,bool)> merger = overwrite<bool>() ){
  set( mm, true , merger );
}
void add( K min, K max , std::function<bool(bool,bool)> merger = overwrite<bool>() ){
  set( min, max , true , merger );
}

RangeSet<K> & operator+=( const RangeSet<K> &s ){
  add( s );
  return this;
}
RangeSet<K> & operator+( const RangeSet<K> s){

}

};

}

#endif
