// Copyright (C) 2010-2011 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#ifndef cf3_UFEM_ComputeTfluid_hpp
#define cf3_UFEM_ComputeTfluid_hpp


#include "solver/ActionDirector.hpp"
#include <solver/actions/Proto/BlockAccumulator.hpp>

#include "LibUFEM.hpp"

#include "LSSAction.hpp"

namespace cf3 {
  namespace math { namespace LSS { class System; } }
  namespace mesh { class Region; }
namespace UFEM {

/// Calculate the heat flux from the one domain and apply is as a Neumann
/// boundary condition to problem on the adjacent domain
/// The "regions" option determines the boundary on which to set the condition
/// The "gradient_region" option determines the region in which the temperature gradient
/// is calculated
/// The "lss" option determines the linear system to which the boundary condition is applied
/// The "temperature_field_tag" option determines the tag to use when looking for the temperature field
class UFEM_API ComputeTfluid : public solver::ActionDirector
{
public:

  /// Contructor
  /// @param name of the component
  ComputeTfluid ( const std::string& name );
  
  virtual ~ComputeTfluid();

  /// Get the class name
  static std::string type_name () { return "ComputeTfluid"; }

private:

  /// Called when the "lss" or "temperature_field_tag" options are changed
  void trigger_setup();

  cf3::solver::actions::Proto::SystemRHS m_rhs;
  PhysicsConstant h;

};

} // UFEM
} // cf3


#endif // cf3_UFEM_ComputeTfluid_hpp
