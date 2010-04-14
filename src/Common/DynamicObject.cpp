#include "Common/DynamicObject.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace CF {
namespace Common {

////////////////////////////////////////////////////////////////////////////////

SignalError::SignalError ( const Common::CodeLocation& where, const std::string& what)
: Common::Exception(where, what, "SignalError")
{}

////////////////////////////////////////////////////////////////////////////////

std::vector < std::pair < Signal::id_t, Signal::desc_t > > DynamicObject::list_signals () const
{
  std::vector < std::pair < Signal::id_t, Signal::desc_t > > result;
  for ( sigmap_t::const_iterator itr = m_signals.begin() ; itr != m_signals.end() ; ++itr )
    result.push_back ( make_pair ( itr->first , itr->second.second ) );
  return result;
}

////////////////////////////////////////////////////////////////////////////////

Signal::return_t DynamicObject::call_signal ( const Signal::id_t& sname, const Signal::arg_t& sinput )
{
  return ( *get_signal ( sname ) ) ( sinput );
}

////////////////////////////////////////////////////////////////////////////////

boost::shared_ptr<DynamicObject::signal_t> DynamicObject::get_signal ( const Signal::id_t& sname )
{
  sigmap_t::iterator itr = m_signals.find(sname);
  if ( itr != m_signals.end() )
    return itr->second.first;
  else
    throw SignalError ( FromHere(), "Signal with name \'" + sname + "\' does not exist" );
}

////////////////////////////////////////////////////////////////////////////////

boost::shared_ptr<DynamicObject::signal_t> DynamicObject::create_signal ( const Signal::id_t& sname,  const Signal::desc_t& desc )
{
  sigmap_t::iterator itr = m_signals.find (sname);
  if ( itr == m_signals.end() )
  {
    boost::shared_ptr < signal_t > ptr ( new signal_t() );
    m_signals.insert ( make_pair ( sname , make_pair ( ptr , desc ) )  );
    return ptr;
  }
  else
    throw SignalError ( FromHere(), "Signal with name \'" + sname + "\' already exists" );
}

////////////////////////////////////////////////////////////////////////////////

boost::shared_ptr<DynamicObject::signal_t> DynamicObject::regist_signal ( const Signal::id_t& sname,  const Signal::desc_t& desc )
{
  sigmap_t::iterator itr = m_signals.find (sname);
  if ( itr == m_signals.end() )
  {
    boost::shared_ptr < signal_t > ptr ( new signal_t() );
    m_signals.insert ( make_pair ( sname , make_pair ( ptr , desc ) )  );
    return ptr;
  }
  else
    return itr->second.first;
}

////////////////////////////////////////////////////////////////////////////////

} // namespace Common
} // namespace CF

////////////////////////////////////////////////////////////////////////////////

