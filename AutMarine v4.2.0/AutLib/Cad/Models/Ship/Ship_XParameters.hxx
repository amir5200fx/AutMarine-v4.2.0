#pragma once
#ifndef _Ship_XParameters_Header
#define _Ship_XParameters_Header

#include <TColStd_Ary1dOfReal.hxx>
#include <Standard_Stream.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Ship_XParameters
		{

		private:

			TColStd_Ary1dOfReal xXCoords_;
			TColStd_Ary1dOfReal xYCoords_;
			TColStd_Ary1dOfReal xZCoords_;

			TColStd_Ary1dOfReal xDepth_;
			TColStd_Ary1dOfReal xSheer_;

			TColStd_Ary1dOfReal xTightness_;
			TColStd_Ary1dOfReal xFlare_;
			TColStd_Ary1dOfReal xDeadRise_;
			TColStd_Ary1dOfReal xSideSlope_;
			TColStd_Ary1dOfReal xSideSlopeAngle_;
			TColStd_Ary1dOfReal xSkeg_;

			TColStd_Ary1dOfReal xRake_;

		public:

			Ship_XParameters();

			TColStd_Ary1dOfReal& XCoords();

			TColStd_Ary1dOfReal& YCoords();

			TColStd_Ary1dOfReal& ZCoords();

			TColStd_Ary1dOfReal& Depth();

			TColStd_Ary1dOfReal& Sheer();

			TColStd_Ary1dOfReal& Tightness();

			TColStd_Ary1dOfReal& Flare();

			TColStd_Ary1dOfReal& DeadRise();

			TColStd_Ary1dOfReal& SideSlope();

			TColStd_Ary1dOfReal& SideSlopeAngle();

			TColStd_Ary1dOfReal& Skeg();

			TColStd_Ary1dOfReal& Rake();

			const TColStd_Ary1dOfReal& XCoords() const;

			const TColStd_Ary1dOfReal& YCoords() const;

			const TColStd_Ary1dOfReal& ZCoords() const;

			const TColStd_Ary1dOfReal& Depth() const;

			const TColStd_Ary1dOfReal& Sheer() const;

			const TColStd_Ary1dOfReal& Tightness() const;

			const TColStd_Ary1dOfReal& Flare() const;

			const TColStd_Ary1dOfReal& DeadRise() const;

			const TColStd_Ary1dOfReal& SideSlope() const;

			const TColStd_Ary1dOfReal& SideSlopeAngle() const;

			const TColStd_Ary1dOfReal& Skeg() const;

			const TColStd_Ary1dOfReal& Rake() const;

			void ExportYCoordsToTecPlot(fstream& File) const;

			void ExportZCoordsToTecPlot(fstream& File) const;

			void ExportDepthToTecPlot(fstream& File) const;

			void ExportSheerToTecPlot(fstream& File) const;

			void ExportTightnessToTecPlot(fstream& File) const;

			void ExportFlareToTecPlot(fstream& File) const;

			void ExportDeadRiseToTecPlot(fstream& File) const;

			void ExportSideSlopeToTecPlot(fstream& File) const;

			void ExportSkegToTecPlot(fstream& File) const;

			void ExportRakeToTecPlot(fstream& File) const;

			void AllocateMemory(const Standard_Integer nbSections);
		};
	}
}

#include <Ship_XParametersI.hxx>

#endif // !_Ship_XParameters_Header
