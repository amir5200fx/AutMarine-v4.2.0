#pragma once
#ifndef _Ship_SectionControlPoints_Header
#define _Ship_SectionControlPoints_Header

#include <TColGeom_Ary1dOfPnt3d.hxx>
#include <Standard_Stream.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Ship_SectionControlPoints
		{

		private:

			Standard_Integer CornerIndex_;

			Standard_Integer nbControlPoints_;

			TColGeom_Ary1dOfPnt3d ControlPoints_;

		public:

			Ship_SectionControlPoints(Standard_Integer nbControlPoints = 0);

			void SetPoints(const TColGeom_Ary1dOfPnt3d& PointList);

			void SetPoint(const Standard_Integer Index, const Geom_Pnt3d& Coord);

			void SetCorner(const Standard_Integer Index);

			const TColGeom_Ary1dOfPnt3d& ControlPoints() const;

			TColGeom_Ary1dOfPnt3d& ControlPoints();

			Standard_Integer Corner() const;

			Standard_Integer NbPoints() const;

			void ExportToTecPlot(fstream& File) const;

		private:

			void AllocateMemory();
		};
	}
}

#endif // !_Ship_SectionControlPoints_Header
