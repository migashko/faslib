#ifndef FAS_SERIALIZATION_JSON_RPC_METHOD_AD_ID_HPP
#define FAS_SERIALIZATION_JSON_RPC_METHOD_AD_ID_HPP
#include <set>

namespace fas{ namespace json{ namespace rpc{ namespace method{

template<typename C = std::set<int> >
class ad_id
{
public:
  
  typedef C container_type;
  
  ad_id()
    :_current_id(-1)
  {
  }
  
  void push(int id) 
  {
    if ( _current_id != -1)
      _ids.insert(_current_id);
    _current_id = id;
  }
  
  void pop(int id) 
  {
    if ( id == _current_id)
      _current_id = -1;
    else
      _ids.erase(id);
  }
  
  bool has(int id)
  {
    return id == _current_id 
           || _ids.find(id)!=_ids.end();
  }
  
private:
  int _current_id;
  container_type _ids;
};

}}}}

#endif
