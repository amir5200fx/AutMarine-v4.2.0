#pragma once
#ifndef _Mesh3d_QualityMap_Header
#define _Mesh3d_QualityMap_Header

#include <Standard_TypeDef.hxx>
#include <Geom_Pnt3d.hxx>
#include <Mesh3d_Node.hxx>
#include <TColMesh3d_HAry1dOfOptTetInfo.hxx>
#include <TColGeom_Ary1dOfPnt3d.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_QualityMap
		{

		public:

			virtual Standard_Real CalcQuality(const Geom_Pnt3d& theP0, const Geom_Pnt3d& theP1, const Geom_Pnt3d& theP2, const Geom_Pnt3d& theP3) const = 0;

			virtual Standard_Real GetInitialAlpha(const TColMesh3d_HAry1dOfOptTetInfo& incidenttets, const Geom_Pnt3d& d, const Standard_Real r, const Standard_Real RateEpsilon, const Standard_Real theWorst) const = 0;

			virtual void GetActiveSet(const TColMesh3d_HAry1dOfOptTetInfo& incidenttets, const Standard_Real theActiveSetFactor, const Standard_Real theWorst, TColGeom_Ary1dOfPnt3d& theActiveGrads) const = 0;

			virtual void CalcOptInfo(const Global_Handle(Mesh3d_Node) theNode, Mesh3d_OptTetInfo& theTet) const = 0;

			//virtual Standard_Real CalcVolume(const Geom_Pnt3d& theP0, const Geom_Pnt3d& theP1, const Geom_Pnt3d& theP2, const Geom_Pnt3d& theP3) const = 0;
		};
	}
}

#endif // !_Mesh3d_QualityMap_Header
