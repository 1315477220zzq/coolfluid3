#ifndef CF_Common_DynamicObject_hh
#define CF_Common_DynamicObject_hh

////////////////////////////////////////////////////////////////////////////////

#include <boost/shared_ptr.hpp>
#include <boost/signals2/signal.hpp>

#include "Common/Exception.hpp"
#include "Common/NonInstantiable.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace CF {
namespace Common {

////////////////////////////////////////////////////////////////////////////////

/// Exception thrown when errors detected while accessing a signal in DynamicObject
/// @author Tiago Quintino
class Common_API SignalError : public Common::Exception {
public:

  /// Constructor
  SignalError (const Common::CodeLocation& where, const std::string& what);

}; // end of class Signal

////////////////////////////////////////////////////////////////////////////////

/// Class that harbours the types handled by the DynamicObject
struct Signal : public NonInstantiable<Signal>
{
    /// signal key
    typedef std::string id_t;
    /// signal description
    typedef std::string desc_t;
    /// signal return type
    typedef std::string return_t;
    /// signal argument
    typedef std::string arg_t;
};

/// DynamicObject executes calls rpvided by string by issuing singals to the slots
/// Slots may be:
///  * its own derived classes that regist  member functions to be called dynamically
///  * other classes that regist themselves to be notified when a signal is issued
///
/// @author Tiago Quintino
class Common_API DynamicObject
{

  public:

  /// combiner which returns the conbined result of all slots
  template <typename T> struct result_xml
  {
    typedef T result_type;
    template<typename InputIterator>
    T operator()(InputIterator first, InputIterator last) const
    {
      // If there are no slots to call, just return the default-constructed value
      if (first == last ) return T();
      T result = *first++;
      while (first != last)
      {
        result += *first;
        ++first;
      }
      return result;
    }
  };

  public:

    typedef boost::signals2::signal< Signal::return_t ( Signal::arg_t ) , result_xml < Signal::return_t > >  signal_t;
    typedef std::map < Signal::id_t , std::pair< boost::shared_ptr< signal_t > , Signal::desc_t > >  sigmap_t;

  public:

    /// Get the list of signals and respective descriptions
    std::vector < std::pair < Signal::id_t, Signal::desc_t > > list_signals () const;

    /// Calls the signal by providing its name and input
    Signal::return_t call_signal ( const Signal::id_t& sname, const Signal::arg_t& sinput );

    /// Get a signal by providing its name
    boost::shared_ptr<signal_t> get_signal ( const Signal::id_t& sname );

    /// Regist signal
    boost::shared_ptr<signal_t> regist_signal ( const Signal::id_t& sname,  const Signal::desc_t& desc );

    /// Adds a dynamic function slot to a signal in itself
    template < typename FTYPE >
    boost::shared_ptr<signal_t> add_dynamic_function ( const Signal::id_t& sname, FTYPE* pfunc, const Signal::desc_t& desc = "" )
    {
        return regist_signal ( sname , desc )->connect ( boost::bind ( pfunc, this, _1 ) );
    }

  protected: // functions
    /// Create a signal
    boost::shared_ptr<signal_t> create_signal ( const Signal::id_t& sname,  const Signal::desc_t& desc );

  protected: // data
    /// storage of the signals
    sigmap_t  m_signals;

}; // class DynamicObject

////////////////////////////////////////////////////////////////////////////////

} // namespace Common
} // namespace CF

////////////////////////////////////////////////////////////////////////////////

#endif // CF_Common_DynamicObject_hh
