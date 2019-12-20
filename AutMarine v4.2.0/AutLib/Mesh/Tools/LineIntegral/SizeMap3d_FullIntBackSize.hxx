#pragma once
#ifndef _SizeMap3d_FullIntBackSize_Header
#define _SizeMap3d_FullIntBackSize_Header

#include <SizeMap3d_StdBackSize.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class SizeMap3d_FullIntBackSize : public SizeMap3d_StdBackSize
		{

		private:

			Standard_Real theTolerance_;

			Standard_Integer theMaxIters_;

			mutable Geom_Pnt3d theOptPoint_;

		public:

			SizeMap3d_FullIntBackSize(const Standard_Real BaseSize, const M_GEO GeoMesh_BackGroundMesh3d& BackGround);

			virtual Standard_Real ElementSize(const Mesh3d_Facet& Facet) const;

			virtual Standard_Real CalcUnitDistance(const Geom_Pnt3d& P1, const Geom_Pnt3d& P2) const;

			virtual Geom_Pnt3d CalcOptimumCoord(const Standard_Real Size, const Mesh3d_Facet& Facet) const;

			virtual Standard_Real MetricIntegrand(const Geom_Pnt3d& Point, const Geom_Pnt3d& Vector) const;

			void SetInnerIteration(const Standard_Integer NbIterations);
		};
	}
}

#include <SizeMap3d_FullIntBackSizeI.hxx>

#endif // !_SizeMap3d_FullIntBackSize_Header
