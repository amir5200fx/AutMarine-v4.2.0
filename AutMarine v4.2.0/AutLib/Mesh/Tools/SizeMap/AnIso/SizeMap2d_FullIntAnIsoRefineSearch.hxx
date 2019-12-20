#pragma once
#ifndef _SizeMap2d_FullIntAnIsoRefineSearch_Header
#define _SizeMap2d_FullIntAnIsoRefineSearch_Header

#include <SizeMap2d_FullIntAnIso.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class SizeMap2d_FullIntAnIsoRefineSearch : public SizeMap2d_FullIntAnIso
		{

		private:

			mutable Standard_Real theCorrectionFactor_;

		public:

			SizeMap2d_FullIntAnIsoRefineSearch(const Global_Handle(Mesh2d_SizeMap) theSizeMap, const Global_Handle(Mesh2d_MetricMap) theMetricMap);

			virtual Geom_Pnt2d CalcOptimumPoint(const Standard_Real Size, const Mesh2d_Edge& Edge) const;

			virtual M_GEO Entity_Box2d CalcSearchRegion(const Standard_Real Radius, const Geom_Pnt2d& Centre, const Mesh2d_Edge& Edge) const;
		};
	}
}

#include <SizeMap2d_FullIntAnIsoRefineSearchI.hxx>

#endif // !_SizeMap2d_FullIntAnIsoRefineSearch_Header
