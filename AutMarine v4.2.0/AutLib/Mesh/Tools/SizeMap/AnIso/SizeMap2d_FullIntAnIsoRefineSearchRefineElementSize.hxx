#pragma once
#ifndef _SizeMap2d_FullIntAnIsoRefineSearchRefineElementSize_Header
#define _SizeMap2d_FullIntAnIsoRefineSearchRefineElementSize_Header

#include <SizeMap2d_FullIntAnIso.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class SizeMap2d_FullIntAnIsoRefineSearchRefineElementSize : public SizeMap2d_FullIntAnIso
		{

		private:

			mutable Standard_Real theCorrectionFactor_;

			Standard_Real theCoeff_;
			Standard_Real theDelta_;

			mutable Geom_Pnt2d theInitCoord_;

		public:

			SizeMap2d_FullIntAnIsoRefineSearchRefineElementSize(const Global_Handle(Mesh2d_SizeMap) theSizeMap, const Global_Handle(Mesh2d_MetricMap) theMetricMap, const Standard_Real theCoefficent = 0.3, const Standard_Real theDelta = 0.2);

			virtual Standard_Real ElementSize(const Mesh2d_Edge& Edge) const;

			//virtual Geom_Pnt2d CalcOptimumPoint(const Standard_Real Size, const Mesh2d_Edge& Edge) const;

			virtual M_GEO Entity_Box2d CalcSearchRegion(const Standard_Real Radius, const Geom_Pnt2d& Centre, const Mesh2d_Edge& Edge) const;

		private:

			Geom_Pnt2d CalcInitOptimumPoint(const Standard_Real Size, const Mesh2d_Edge& Edge) const;
		};
	}
}

#include <SizeMap2d_FullIntAnIsoRefineSearchRefineElementSizeI.hxx>

#endif // !_SizeMap2d_FullIntAnIsoRefineSearchRefineElementSize_Header