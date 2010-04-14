#ifndef COOLFluiD_MathTools_IntersectSolver_hh
#define COOLFluiD_MathTools_IntersectSolver_hh

//////////////////////////////////////////////////////////////////////////////

#include "MatrixIntersect.hh"

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace MathTools {

//////////////////////////////////////////////////////////////////////////////

/// This class represents a eigen value solver for symmetric matrices
/// based on Jacobi algorithm
/// @author Jurek Majewski
class MathTools_API IntersectSolver : public MatrixIntersect
{
public:

  /// Default constructor without arguments
  IntersectSolver() : MatrixIntersect() {}

  /// Default destructor
  ~IntersectSolver()  {}

  /// Finds an eigenvalues and eigenvectors of matrix a
  /// @param a    input matrix - it will be modified during calculation
  /// @param r    result: left eigenvectors matrix
  /// @param lam  result: vector of eigenvalues
  void intersectCalc( const RealMatrix& a, const RealMatrix& b, RealMatrix& res );

}; // end of class IntersectSolver

//////////////////////////////////////////////////////////////////////////////

  } // namespace MathTools

} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////

#endif // COOLFluiD_MathTools_IntersectSolver_hh
