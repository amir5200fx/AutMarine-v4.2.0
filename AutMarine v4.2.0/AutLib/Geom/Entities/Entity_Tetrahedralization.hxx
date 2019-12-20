#pragma once
#ifndef _Entity_Tetraderalization_Header
#define _Entity_Tetraderalization_Header

#include <TColEntity_Ary1dOfTetrahedronIndex.hxx>
#include <TColGeom_Ary1dOfPnt3d.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Entity_Tetrahedralization
		{

		private:

			TColGeom_Ary1dOfPnt3d thePoints_;

			TColEntity_Ary1dOfTetrahedronIndex theTetrahedros_;

		public:

			Entity_Tetrahedralization();

			Entity_Tetrahedralization(const TColGeom_Ary1dOfPnt3d& Coords, const TColEntity_Ary1dOfTetrahedronIndex& Tetrahedrons);

			Standard_Integer NbPoints() const;

			Standard_Integer NbTetrahedrons() const;

			const TColGeom_Ary1dOfPnt3d& Points() const;

			TColGeom_Ary1dOfPnt3d& Points();

			const TColEntity_Ary1dOfTetrahedronIndex& Tetrahedrons() const;

			TColEntity_Ary1dOfTetrahedronIndex& Tetrahedrons();

			void ExportToPlt(fstream& File) const;
		};
	}
}

#include <Entity_TetrahedralizationI.hxx>

#endif // !_Entity_Tetraderalization_Header
