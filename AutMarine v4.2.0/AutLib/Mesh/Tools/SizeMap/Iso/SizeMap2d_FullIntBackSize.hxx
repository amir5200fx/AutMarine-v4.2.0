#pragma once
#ifndef _Mesh2d_FullIntBackSize_Header
#define _Mesh2d_FullIntBackSize_Header

#include <SizeMap2d_StdBackSize.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class SizeMap2d_FullIntBackSize : public SizeMap2d_StdBackSize
		{

		private:

			Standard_Real theTolerance_;

			Standard_Integer theMaxIters_;

			mutable Geom_Pnt2d theOptPoint_;

		public:

			SizeMap2d_FullIntBackSize(const Standard_Real BaseSize, const M_GEO GeoMesh_BackGroundMesh2d& BackGround);

			virtual Standard_Real ElementSize(const Mesh2d_Edge& Edge) const;

			virtual Standard_Real CalcUnitDistance(const Geom_Pnt2d& P1, const Geom_Pnt2d& P2) const;

			virtual Geom_Pnt2d CalcOptimumPoint(const Standard_Real Size, const Mesh2d_Edge& Edge) const;

			virtual Standard_Real MetricIntegrand(const Geom_Pnt2d& Point, const Geom_Pnt2d& Vector) const;

			void SetInnerIteration(const Standard_Integer NbIterations);
		};
	}
}

#include <SizeMap2d_FullIntBackSizeI.hxx>

#endif // !_Mesh2d_FullIntBackSize_Header
