#pragma once
#ifndef _Duct_SectionControlPoints_Header
#define _Duct_SectionControlPoints_Header

#include <TColGeom_Ary1dOfPnt3d.hxx>
#include <Standard_Stream.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Duct_SectionControlPoints
		{

		private:

			TColGeom_Ary1dOfPnt3d theControlPoints_;

		public:

			Duct_SectionControlPoints();

			Standard_Integer NbPoints() const;

			const TColGeom_Ary1dOfPnt3d& ControlPoints() const;

			const Geom_Pnt3d& Coord(const Standard_Integer theIndex) const;

			TColGeom_Ary1dOfPnt3d& ControlPoints();

			void SetPoints(const TColGeom_Ary1dOfPnt3d& thePointList);

			void SetPoint(const Standard_Integer theIndex, const Geom_Pnt3d& theCoord);

			void ExportToTecPlot(fstream& File) const;
		};
	}
}

#include <Duct_SectionControlPointsI.hxx>

#endif // !_Duct_SectionControlPoints_Header
