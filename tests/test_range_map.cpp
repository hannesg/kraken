#include "kraken/range_map.h"
#include <stdio.h>

#define EXPECT_VALUE( rm, k ,v ) \
  if( rm[k] != v){ \
    printf("\nExpected %d for rm[%d], got %d.\n", v, k, rm[k]);\
  }else{\
    printf(".");\
  }


int test_range_map1(){

  Kraken::RangeMap<int, int> rm;

  rm.set(0, 10, 1, [](int a ,int b ){ return b; } );

  if( rm[0] != 1){
    printf("Expected 1 for rm[0], got %d.\n", rm[0]);
  }
  if( rm[10] != 1){
    printf("Expected 1 for rm[10], got %d.\n", rm[10]);
  }
  if( rm[11] != 0){
    printf("Expected 0 for rm[11], got %d.\n", rm[11]);
  }
  return 0;
}

int test_range_map2(){

  Kraken::RangeMap<int, int> rm;

  rm.set(0, 10, 1);
  rm.set(2,  5, 2);

  EXPECT_VALUE( rm, 0, 1);
  EXPECT_VALUE( rm, 2, 2);
  EXPECT_VALUE( rm,10, 1);
  EXPECT_VALUE( rm,11, 0);
  return 0;
}

int test_range_map3(){

  Kraken::RangeMap<int, int> rm;
  Kraken::RangeSet<int> rs = Kraken::RangeSet<int>();
  rs.set(4,  7, true);
  rs.set(12, 15, true);
  rm.set(0, 10, 1);
  rm.set(2,  5, 2);
  rm.set( rs, 4 );

  EXPECT_VALUE( rm, 0, 1);
  EXPECT_VALUE( rm, 2, 2);
  EXPECT_VALUE( rm, 4, 4);
  EXPECT_VALUE( rm, 7, 4);
  EXPECT_VALUE( rm, 8, 1);
  EXPECT_VALUE( rm,10, 1);
  EXPECT_VALUE( rm,11, 0);
  EXPECT_VALUE( rm,12, 4);
  EXPECT_VALUE( rm,15, 4);
  return 0;
}

Kraken::RangeMap<int, int> get_rm(){
  Kraken::RangeMap<int, int> rm1;
  rm1.set( 4, 5, 1);
  rm1.set( 7, 10, 2);
  return rm1;
}

int test_range_map4(){

  Kraken::RangeMap<int, int> rm2 = get_rm();
  Kraken::RangeMap<int, int> rm3 = rm2;
  
 
  return 0;
}

int test_range_map5(){

  Kraken::RangeMap<int, int> rm;

  rm.set(0, 10, 1);
  rm.set(2,  5, 2);

  EXPECT_VALUE( rm, 0, 1);
  EXPECT_VALUE( rm, 2, 2);
  EXPECT_VALUE( rm, 5, 2);
  EXPECT_VALUE( rm, 6, 1);
  EXPECT_VALUE( rm,10, 1);

  rm.replace(2, 3);

  EXPECT_VALUE( rm, 0, 1);
  EXPECT_VALUE( rm, 2, 3);
  EXPECT_VALUE( rm, 5, 3);
  EXPECT_VALUE( rm, 6, 1);
  EXPECT_VALUE( rm,10, 1);


  return 0;
}


int main( int argc, char** argv){

  test_range_map1();
  test_range_map2();
  test_range_map3();
  test_range_map4();
  test_range_map5();
  return 0;
}
