#ifndef FAS_JSONRPC_METHOD_AD_METHOD_IDS_HPP
#define FAS_JSONRPC_METHOD_AD_METHOD_IDS_HPP

#include <set>

namespace fas{ namespace jsonrpc{ 

// for id only greater zero
template<typename C = std::set<int> >
class ad_method_id
{
public:

  typedef C container_type;
  
  ad_method_id(): _current_id(-1) { }
  
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

  int new_id() { return 1; }

  void push(int id) { _current_id = id; }
  
  void pop(int id)  { _current_id = -1; }
  
  bool has(int id) const { return id == _current_id; }
  
private:
  int _current_id;
};

class ad_ids_empty
{
public:

  int new_id() { return 1; }
  
  void push(int id) {  }
  
  void pop(int id)  {  }
  
  bool has(int id) const  { return true; }
};

class ad_no_ids
{
public:

  int new_id() { return 1; }

  void push(int id) {  }
  
  void pop(int id)  {  }
  
  bool has(int id) const  { return false; }
};


}}

#endif
