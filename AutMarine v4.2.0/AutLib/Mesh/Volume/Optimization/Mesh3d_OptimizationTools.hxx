#pragma once
#ifndef _Mesh3d_OptimizationTools_Header
#define _Mesh3d_OptimizationTools_Header

#include <TColGeom_Ary1dOfPnt3d.hxx>
#include <TColMesh3d_HAry1dOfOptimizationTetInfo.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_OptimizationTools
		{

		public:

			static Standard_Real GetInitialAlpha(const TColMesh3d_HAry1dOfOptimizationTetInfo& theElements, Geom_Pnt3d& d, const Standard_Real r, const Standard_Real theWorst);

			static Geom_Pnt3d MinConvexHullPoint(const TColGeom_Ary1dOfPnt3d& thePoints);

			static void FindBasis(const TColGeom_Ary1dOfPnt3d& S, const TColGeom_Ary1dOfPnt3d& M, TColGeom_Ary1dOfPnt3d& B, const Standard_Integer SizeS, const Standard_Integer SizeM, Standard_Integer& SizeB);

			static void GetActiveSet(const TColMesh3d_HAry1dOfOptimizationTetInfo& theElements, const Standard_Real theActiveSetFactor, TColGeom_Ary1dOfPnt3d& theActiveGrads);
			
		};
	}
}

#endif // !_Mesh3d_OptimizationTools_Header
