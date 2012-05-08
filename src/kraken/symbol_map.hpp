
namespace Kraken{

template< typename K, typename V, V NIL >
class RangeMap {

public:

  SymbolMap
  V operator[](const K& key);

private:
  K min;
  K max;
  SymbolMap<K,V,NIL>* left;
  SymbolMap<K,V,NIL>* right;
  V value;
};

}
