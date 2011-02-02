// Copyright (C) 2010 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#ifndef CF_Solver_CEigenLSS_hpp
#define CF_Solver_CEigenLSS_hpp

////////////////////////////////////////////////////////////////////////////////

#include "Common/Component.hpp"

#include "Math/MatrixTypes.hpp"

#include "Mesh/CMesh.hpp"

#include "LibSolver.hpp"

namespace CF {
namespace Solver {

////////////////////////////////////////////////////////////////////////////////

/// CEigenLSS component class
/// This class stores a linear system for use by proto expressions
/// @author Bart Janssens
class Solver_API CEigenLSS : public Common::Component {

public: // typedefs

  typedef boost::shared_ptr<CEigenLSS> Ptr;
  typedef boost::shared_ptr<CEigenLSS const> ConstPtr;

public: // functions

  /// Contructor
  /// @param name of the component
  CEigenLSS ( const std::string& name );

  /// Get the class name
  static std::string type_name () { return "CEigenLSS"; }    
  
  /// Set the number of equations
  void resize ( Uint nb_dofs );
  
  /// Number of equations
  Uint size() const;
  
  /// Reference to the system matrix
  RealMatrix& matrix();
  
  /// Reference to the RHS vector
  RealVector& rhs();
  
  /// Const access to the solution
  const RealVector& solution();
  
  /// Solve the system and store the result in the solution vector
  void solve();
  
private:
  /// System matrix
  RealMatrix m_system_matrix;
  
  /// Right hand side
  RealVector m_rhs;
  
  /// Solution
  RealVector m_solution;
};

/// Helper function to increment the solution field(s) with the given solution vector from a LSS, i.e. treat the solution vector as the differece between the new  and old field values
void increment_solution(const RealVector& solution, const std::vector<std::string>& field_names, const std::vector<std::string>& var_names, const std::vector<Uint>& var_sizes, Mesh::CMesh& solution_mesh);

////////////////////////////////////////////////////////////////////////////////

} // Solver
} // CF


////////////////////////////////////////////////////////////////////////////////

#endif // CF_Solver_CEigenLSS_hpp
