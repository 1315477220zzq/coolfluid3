#ifndef COOLFluiD_MathTools_MathFunctions_hh
#define COOLFluiD_MathTools_MathFunctions_hh

//////////////////////////////////////////////////////////////////////////////

#include "Common/COOLFluiD.hh"
#include "Common/NonInstantiable.hh"
#include "MathTools/MathTools.hh"

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace MathTools {

//////////////////////////////////////////////////////////////////////////////

/// Provides an a set of static functions for various useful operations
/// @author Andrea Lani
/// @author Tiago Quintino
/// @author Mehmet Sarp Yalim
class MathFunctions : public Common::NonInstantiable<MathFunctions> {
public:

  /// Signum function
  /// @param value the real to which infer the sign
  /// @return -1.0 if value < 0.0
  /// @return 0.0 if value = 0.0
  /// @return 1.0 if value > 0.0
  static CFreal signum (const CFreal& value)
  {
    if ( value <  0.0 )  return -1.0;
    if ( value == 0.0 )  return 0.0;
    return 1.0;
  }

  /// Sign function
  /// @param value the real to which infer the sign
  /// @return -1.0 if value < 0.0
  /// @return 1.0 if value >= 0.0
  static CFreal sign(const CFreal& value)
  {
    if (value < 0.0) return -1.0;
    else return 1.0;
  }
  
  /**
   * Change the sign of the first argument with the sign
   * of the second argument
   *
   * @param   value   the value of this will be returned
   * @param   newSignValue   the sign of what will be returned
   * @return  the value with the sign of newSignValue
   */
  static CFreal changeSign(const CFreal& value, const CFreal& newSignValue)
  {
    return newSignValue >= 0 ? (value >=0 ? value : -value) : (value >= 0 ? -value : value);
  }

  /// Heavyside function
  /// @param value is real
  /// @return 1.0 if value > 0.0
  /// @return 0.0 if value < 0.0
  /// @return 0.5 if value = 0.0
  static CFreal heavyside(const CFreal& value)
  {
    if (value < 0.0) return 0.0;
    if (value == 0.0) return 0.5;
    return 1.0;
  }

  /// Calculate the euclidean distance between two "points"
  /// (Node, State, RealVector, ...)
  /// @pre T1 and T2 must have the overloading of the operator[] implemented
  template <class T1, class T2>
  static CFreal getDistance(const T1& n1, const T2& n2)
  {
    cf_assert(n1.size() == n2.size());

    CFreal dist = 0.;
    const CFuint size =  n1.size();
    for (CFuint i = 0; i < size; ++i)
    {
      const CFreal diff = n1[i] - n2[i];
      dist += diff*diff;
    }
    return std::sqrt(dist);
  }

  /**
   * Calculate the faculty
   *
   * @param   n   calculate faculty of this number
   * @return  faculty of n
   */
  static CFuint faculty(const CFuint& n)
  {
    if (n<2)
  		return 1;
  	else
  		return (n*faculty(n-1));
  }
  
  /// Mixed Product of three vectors
  /// @pre size() == 3 == v1.size() == v2.size() == v3.size() == temp.size()
  ///      (cf_assertion can check this)
  /// @param v1   first vector
  /// @param v2   second vector
  /// @param v3   third vector
  /// @param temp temporary vector
  /// @return the mixed product
  template <class T1, class T2, class T3, class T4>
  static CFreal mixedProd (const T1& v1,
                           const T2& v2,
                           const T3& v3,
                           T4& temp)
  {
    // sanity checks
    cf_assert(v1.size() == 3);
    cf_assert(v2.size() == 3);
    cf_assert(v3.size() == 3);
    cf_assert(temp.size() == 3);

    MathFunctions::crossProd(v1, v2, temp);
    return MathFunctions::innerProd(v3, temp);
  }

  /// Cross Product for vector*vector operations
  /// @pre v1.size() == v2.size() == result.size() == 3
  /// @param v1 first vector
  /// @param v2 second vector
  /// @param result vector storing the result
  template <class T1, class T2, class T3>
  static void crossProd (const T1& v1,
                         const T2& v2,
                         T3& result)
  {
    // sanity checks
    cf_assert(v1.size() == 3);
    cf_assert(v2.size() == 3);
    cf_assert(result.size() == 3);

    result[0] =  v1[1]*v2[2] - v1[2]*v2[1];
    result[1] = -v1[0]*v2[2] + v1[2]*v2[0];
    result[2] =  v1[0]*v2[1] - v1[1]*v2[0];
  }

  /// Internal Product for vector*vector operations
  /// \f$ s = v \cdot v1 \f$.
  /// Objects must be of same size.
  /// @param v1 first vector
  /// @param v2 second vector
  /// @return the inner product of the two given vectors
  template <class T1, class T2>
  static CFreal innerProd (const T1& v1, const T2& v2)
  {
    cf_assert(v1.size() == v2.size());

    const CFuint size = v1.size();
    CFreal result = 0.0;
    for (CFuint i = 0; i < size; ++i)
      result += v1[i]*v2[i];
    return result;
  }

  /// Tensor Product for vector*vector operations
  /// \f$ s = v \cdot v1 \f$.
  /// @param v1 first vector
  /// @param v2 second vector
  /// @return the tensor product of the two given vectors
  template <class T1, class T2, class T3>
  static void tensorProd(const T1& v1, const T2& v2, T3& m)
  {
    cf_assert(m.getNbRows()    == v1.size());
    cf_assert(m.getNbColumns() == v2.size());

    const CFuint v1size = v1.size();
    const CFuint v2size = v2.size();
    for (CFuint i = 0; i < v1size; ++i) {
      for (CFuint j = 0; j < v2size; ++j) {
        m(i,j) = v1[i]*v2[j];
      }
    }
  }

}; // end class MathFunctions

//////////////////////////////////////////////////////////////////////////////

  } // namespace MathTools

} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////

#endif // COOLFluiD_MathTools_MathFunctions_hh
