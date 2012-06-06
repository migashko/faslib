#ifndef FAS_RPC_JSON_METHOD_AD_IDS_HPP
#define FAS_RPC_JSON_METHOD_AD_IDS_HPP

#include <set>

namespace fas{ namespace rpc{ namespace json{ 

template<typename C = std::set<int> >
class ad_ids
{
public:

  typedef C container_type;
  
  ad_ids(): _current_id(-1) { }
  
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
  
  bool has(int id) const
  {
    return id == _current_id 
           || _ids.find(id)!=_ids.end();
  }
  
private:
  int _current_id;
  container_type _ids;
};

class ad_ids_simple
{
public:

  ad_ids_simple(): _current_id(-1) { }
  
  void push(int id) { _current_id = id; }
  
  void pop(int id)  { _current_id = -1; }
  
  bool has(int id) const { return id == _current_id; }
  
private:
  int _current_id;
};

class ad_ids_empty
{
public:

  void push(int id) {  }
  
  void pop(int id)  {  }
  
  bool has(int id) const  { return true; }
};

class ad_no_ids
{
public:

  void push(int id) {  }
  
  void pop(int id)  {  }
  
  bool has(int id) const  { return false; }
};


}}}

#endif
