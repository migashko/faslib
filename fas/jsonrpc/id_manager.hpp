#ifndef FAS_JSONRPC_ID_MANAGER_HPP
#define FAS_JSONRPC_ID_MANAGER_HPP

#include <fas/jsonrpc/types.hpp>
#include <set>

namespace fas{ namespace jsonrpc{ 

// for id only greater zero
template<typename C = std::set<id_t> >
class id_manager
{
public:

  typedef C container_type;
  
  id_manager(): _current_id(-1) { }

  id_t new_id()
  {
    id_t id = 1;

    if ( !_ids.empty() )
      id = *(_ids.rbegin()) + 1;
    
    if ( id <= _current_id )
      id = _current_id + 1;

    this->push(id);
    
    return id;
  }
  
  void push(id_t id) 
  {
    if ( _current_id != -1)
      _ids.insert(_current_id);
    _current_id = id;
  }
  
  void pop(id_t id) 
  {
    if ( id == _current_id)
      _current_id = -1;
    else
      _ids.erase(id);
  }
  
  bool has(id_t id) const
  {
    return id == _current_id 
           || _ids.find(id)!=_ids.end();
  }

  size_t size() const
  {
    return ( _current_id == -1 ? 0 : _current_id ) + _ids.size();
  }

  void clear()
  {
    _current_id = 0;
    _ids.clear();
  }
  
private:
  
  id_t _current_id;
  container_type _ids;
};

class simple_id_manager
{
public:

  simple_id_manager(): _current_id(-1) { }

  id_t new_id() { return 1; }

  void push(id_t id) { _current_id = id; }

  void pop(id_t id)  { _current_id = -1; }

  bool has(id_t id) const { return id == _current_id; }

private:
  id_t _current_id;
};

class empty_id_manager
{
public:

  id_t new_id() { return 1; }

  void push(id_t id) {  }

  void pop(id_t id)  {  }

  bool has(id_t id) const  { return true; }
};

class fail_id_manager
{
public:

  id_t new_id() { return 1; }

  void push(id_t id) {  }

  void pop(id_t id)  {  }

  bool has(id_t id) const  { return false; }
};

}}

#endif
