#ifndef FAS_JSONRPC_INVOKE_REMOTE_AD_REMOTE_ID_HPP
#define FAS_JSONRPC_INVOKE_REMOTE_AD_REMOTE_ID_HPP

#include <set>

namespace fas{ namespace jsonrpc{ 

// for id only greater zero
template<typename C = std::set<int> >
class ad_remote_id
{
public:

  typedef C container_type;
  
  ad_remote_id(): _current_id(-1) { }

  int new_id()
  {
    int id = 1;

    if ( !_ids.empty() )
      id = *(_ids.rbegin()) + 1;
    
    if ( id <= _current_id )
      id = _current_id + 1;

    this->push(id);
    
    return id;
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
  
  bool has(int id) const
  {
    return id == _current_id 
           || _ids.find(id)!=_ids.end();
  }
  
private:
  int _current_id;
  container_type _ids;
};

}}

#endif
