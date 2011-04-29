// Copyright (C) 2010 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#ifndef CF_Mesh_SF_LineFluxP2_hpp
#define CF_Mesh_SF_LineFluxP2_hpp

#include "Mesh/ShapeFunction.hpp"
#include "Mesh/GeoShape.hpp"
#include "SFDM/src/SF/LibSF.hpp"

namespace CF {
namespace SFDM {
namespace SF {

class SFDM_SF_API LineFluxP2  : public Mesh::ShapeFunction {
public:

  static const Uint dimensionality = 1;
  static const Uint nb_nodes = 3;
  static const Uint order = 2;
  static const Mesh::GeoShape::Type shape = Mesh::GeoShape::LINE;

public:

  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  /// Constructor
  LineFluxP2(const std::string& name = type_name());

  /// Type name
  static std::string type_name() { return "LineFluxP2"; }

  /// Types for the matrices used
  typedef Eigen::Matrix<Real, dimensionality, 1> MappedCoordsT;
  typedef Eigen::Matrix<Real, 1, nb_nodes> ValueT;
  typedef Eigen::Matrix<Real, dimensionality, nb_nodes> GradientT;
  typedef Eigen::Matrix<Real, nb_nodes, dimensionality> MappedNodesT;

  /// Compute the shape functions corresponding to the given
  /// mapped coordinates
  /// @param mapped_coord The mapped coordinates
  /// @param result Vector storing the result
  static void value(const MappedCoordsT& mapped_coord, ValueT& result);

  /// Compute the gradient with respect to mapped coordinates, i.e. parial derivatives are in terms of the
  /// mapped coordinates. The result needs to be multiplied with the inverse jacobian to get the result in real
  /// coordinates.
  /// @param mapped_coord The mapped coordinates where the gradient should be calculated (dimensionality x nb_nodes)
  /// @param result Storage for the resulting gradient matrix
  static void gradient(const MappedCoordsT& mapped_coord, GradientT& result);

  /// Coordinates in mapped space of the nodes defining the shape function (nb_nodes x dimensionality)
  static const MappedNodesT& mapped_sf_nodes() { return s_mapped_sf_nodes; }

  virtual void compute_value(const RealVector& local_coord, RealRowVector& result)
  {
    value(local_coord,m_tmp_v);
    result = m_tmp_v;
  }

  virtual void compute_gradient(const RealVector& local_coord, RealMatrix& result)
  {
    gradient(local_coord,m_tmp_g);
    result = m_tmp_g;
  }

private:

  static MappedNodesT s_mapped_sf_nodes;
  ValueT    m_tmp_v;
  GradientT m_tmp_g;

};

} // SF
} // SFDM
} // CF

#endif // CF_Mesh_SF_LineFluxP2
