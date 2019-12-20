#pragma once
#ifndef _QualityMap3d_MinSine_Header
#define _QualityMap3d_MinSine_Header

#include <Mesh3d_QualityMap.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class QualityMap3d_MinSine : public Mesh3d_QualityMap
		{

		private:

		public:

			QualityMap3d_MinSine();

			virtual Standard_Real CalcQuality(const Geom_Pnt3d& theP0, const Geom_Pnt3d& theP1, const Geom_Pnt3d& theP2, const Geom_Pnt3d& theP3) const;

			virtual Standard_Real GetInitialAlpha(const TColMesh3d_HAry1dOfOptTetInfo& incidenttets, const Geom_Pnt3d& d, const Standard_Real r, const Standard_Real RateEpsilon, const Standard_Real theWorst) const;

			virtual void GetActiveSet(const TColMesh3d_HAry1dOfOptTetInfo& incidenttets, const Standard_Real theActiveSetFactor, const Standard_Real theWorst, TColGeom_Ary1dOfPnt3d& theActiveGrads) const;

			virtual void CalcOptInfo(const Global_Handle(Mesh3d_Node) theNode, Mesh3d_OptTetInfo& theTet) const;
		};
	}
}

#endif // !_QualityMap3d_MinSine_Header
