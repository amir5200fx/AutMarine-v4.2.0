#pragma once
#ifndef _Duct_XParameters_Header
#define _Duct_XParameters_Header

#include <TColStd_Ary1dOfReal.hxx>
#include <Standard_Stream.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Duct_XParameters
		{

		private:

			TColStd_Ary1dOfReal xXCoords_;
			TColStd_Ary1dOfReal xYCoords_;
			TColStd_Ary1dOfReal xZCoords_;

			TColStd_Ary1dOfReal xUpperTightness_;
			TColStd_Ary1dOfReal xLowerTightness_;
			TColStd_Ary1dOfReal xSideSlope_;
			TColStd_Ary1dOfReal xDepth_;
			TColStd_Ary1dOfReal xWidth_;

		public:

			Duct_XParameters();

			TColStd_Ary1dOfReal& XCoords();

			TColStd_Ary1dOfReal& YCoords();

			TColStd_Ary1dOfReal& ZCoords();

			TColStd_Ary1dOfReal& UpperTightness();

			TColStd_Ary1dOfReal& LowerTightness();

			TColStd_Ary1dOfReal& SideSlope();

			TColStd_Ary1dOfReal& Depth();

			TColStd_Ary1dOfReal& Width();

			const TColStd_Ary1dOfReal& XCoords() const;

			const TColStd_Ary1dOfReal& YCoords() const;

			const TColStd_Ary1dOfReal& ZCoords() const;

			const TColStd_Ary1dOfReal& UpperTightness() const;

			const TColStd_Ary1dOfReal& LowerTightness() const;

			const TColStd_Ary1dOfReal& SideSlope() const;

			const TColStd_Ary1dOfReal& Depth() const;

			const TColStd_Ary1dOfReal& Width() const;

			void ExportYCoordsToTecPlot(fstream& File) const;

			void ExportZCoordsToTecPlot(fstream& File) const;

			void ExportUpperTightnessToTecPlot(fstream& File) const;

			void ExportLowerTightnessToTecPlot(fstream& File) const;

			void ExportSideSlopeToTecPlot(fstream& File) const;

			void ExportWidthToTecPlot(fstream& File) const;

			void AllocateMemory(const Standard_Integer nbSections);
		};
	}
}

#include <Duct_XParametersI.hxx>

#endif // !_Duct_XParameters_Header
