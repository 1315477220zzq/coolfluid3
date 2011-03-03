// Copyright (C) 2010 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#ifndef CF_Solver_CAdvanceTime_hpp
#define CF_Solver_CAdvanceTime_hpp

////////////////////////////////////////////////////////////////////////////////

#include "Solver/Actions/LibActions.hpp"
#include "Common/CAction.hpp"

namespace CF {
namespace Solver {
  class CTime;
namespace Actions {

////////////////////////////////////////////////////////////////////////////////

/// CAdvanceTime models a Unsteady PDE problem
/// @author Tiago Quintino
class Solver_Actions_API CAdvanceTime : public Common::CAction {

public: // typedefs

  typedef boost::shared_ptr<CAdvanceTime> Ptr;
  typedef boost::shared_ptr<CAdvanceTime const> ConstPtr;

public: // functions

  /// Contructor
  /// @param name of the component
  CAdvanceTime ( const std::string& name );

  /// Virtual destructor
  virtual ~CAdvanceTime();

  /// Get the class name
  static std::string type_name () { return "CAdvanceTime"; }

  /// Simulates this model
  virtual void execute();

private:
  
  boost::weak_ptr<CTime> m_time;

};

////////////////////////////////////////////////////////////////////////////////

} // Actions
} // Solver
} // CF

////////////////////////////////////////////////////////////////////////////////

#endif // CF_Solver_CAdvanceTime_hpp