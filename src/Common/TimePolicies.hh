#ifndef COOLFluiD_Common_TimePolicies_hh
#define COOLFluiD_Common_TimePolicies_hh

//////////////////////////////////////////////////////////////////////////////

#include "Common/CF.hh"

#ifdef CF_TIME_WITH_SYS_TIME
    #include <sys/time.h>
    #include <time.h>
#else
  #ifdef CF_HAVE_SYS_TIME_H
    #include <sys/time.h>
  #endif
  #ifdef CF_HAVE_TIME_H
    #include <time.h>
  #endif
#endif

#ifdef CF_HAVE_GETTIMEOFDAY
  #include <sys/time.h>
#endif

#ifdef CF_HAVE_SYS_RESOURCE_H
  #include <sys/resource.h>
#endif

//////////////////////////////////////////////////////////////////////////////

namespace CF {

  namespace Common {

//////////////////////////////////////////////////////////////////////////////

#ifdef CF_HAVE_SYS_RESOURCE_H

/// Implements a time policy that uses rusage when available
/// computes the accurate user time, but not all systems implement it
/// @author Tiago Quintino
class Common_API TimePolicy_rusage {
public:
  /// Default Constructor
  TimePolicy_rusage();
  /// Implements the initializing of the start time
  void initStartTime();
  /// Implements the taking of the stopping time
  void takeStopTime();
  /// Implements returning the elapsed delta
  /// @return elapsed time in seconds
  CF::Real getDelta() const;
  /// Implements the addition of the elapsed time to the accumulated times
  void accumulateTime(CF::Real& accTime);

private:
  /// Gets the time difference in seconds
  CF::Real seconds() const;

private:
  /// starting time
  CF::Real m_start;
  /// stopping time
  CF::Real m_stop;

}; // end class TimePolicy_rusage

#endif // CF_HAVE_SYS_RESOURCE_H

//////////////////////////////////////////////////////////////////////////////

#if defined(CF_HAVE_TIME_H) || defined(CF_HAVE_SYS_TIME_H)

/// Implements a time policy that uses clock()
/// @author Tiago Quintino
class  Common_API TimePolicy_cclock {
public:
  /// Default Constructor
  TimePolicy_cclock();
  /// Implements the initializing of the start time
  void initStartTime();
  /// Implements the taking of the stopping time
  void takeStopTime();
  /// Implements returning the elapsed delta
  /// @return elapsed time in seconds
  CF::Real getDelta() const;
  /// Implements the addition of the elapsed time to the accumulated times
  void accumulateTime(CF::Real& accTime);

private:
  /// Gets the time difference in seconds
  CF::Real seconds() const;

private:
  /// starting time
  CF::Real m_start;
  /// stopping time
  CF::Real m_stop;

}; // end class TimePolicy_cclock

#endif //  defined(CF_HAVE_TIME_H) || defined(CF_HAVE_SYS_TIME_H)

//////////////////////////////////////////////////////////////////////////////

#ifdef CF_HAVE_GETTIMEOFDAY

/// Implements a time policy that uses gettimeofday()
/// @author Tiago Quintino
class  Common_API TimePolicy_gettimeofday {
public:
  /// Default Constructor
  TimePolicy_gettimeofday();
  /// Implements the initializing of the start time
  void initStartTime();
  /// Implements the taking of the stopping time
  void takeStopTime();
  /// Implements returning the elapsed delta
  /// @return elapsed time in seconds
  CF::Real getDelta() const;
  /// Implements the addition of the elapsed time to the accumulated times
  void accumulateTime(CF::Real& accTime);

private:
  ///  Subtract 2 struct timeval 's
  ///  @return true if the result is negative
  bool subTimeval (timeval & Res, const timeval & X1, const timeval & Y1) const;

  /// Convert a struct timeval to a double
  CF::Real toDouble (const timeval & result) const;

private:
  /// starting time
  timeval m_start;
  /// stopping time
  timeval m_stop;
}; // end class TimePolicy_gettimeofday

#endif // CF_HAVE_GETTIMEOFDAY

//////////////////////////////////////////////////////////////////////////////

#ifdef CF_HAVE_GETTIMEOFDAY
    #ifndef CF_WALLTIME
    #define CF_WALLTIME
      typedef TimePolicy_gettimeofday WallTime;
    #endif
#endif // CF_HAVE_GETTIMEOFDAY

#ifdef CF_HAVE_SYS_RESOURCE_H
    #ifndef CF_CPUTIME
    #define CF_CPUTIME
      typedef TimePolicy_rusage CPUTime;
    #endif
#endif // CF_HAVE_SYS_RESOURCE_H

#if defined(CF_HAVE_TIME_H) || defined(CF_HAVE_SYS_TIME_H)
  #ifndef CF_WALLTIME
  #define CF_WALLTIME
    typedef TimePolicy_cclock WallTime;
  #endif
  #ifndef CF_CPUTIME
  #define CF_CPUTIME
    typedef TimePolicy_cclock CPUTime;
  #endif
#endif // defined(CF_HAVE_TIME_H) || defined(CF_HAVE_SYS_TIME_H)

// check that all time where defined
#ifndef CF_WALLTIME
  #error "No time function is present that can provide WallTime"
#endif
#ifndef CF_CPUTIME
  #error "No time function is present that can provide CPUTime"
#endif

//////////////////////////////////////////////////////////////////////////////

  } // namespace Common

} // namespace CF

//////////////////////////////////////////////////////////////////////////////

#endif // COOLFluiD_Common_TimePolicies_hh

