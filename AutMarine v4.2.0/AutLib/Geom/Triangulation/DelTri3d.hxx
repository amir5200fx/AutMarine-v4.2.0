#pragma once
#ifndef _DelTri3d_Header
#define _DelTri3d_Header

#include <Global_Memory.hxx>
#include <TColGeom_Ary1dOfPnt3d.hxx>
#include <TColEntity_Ary1dOfTetrahedronIndex.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class DelTri3d
		{

		private:

			const Global_Handle(TColGeom_Ary1dOfPnt3d) theInsertedPoints_;

			TColGeom_Ary1dOfPnt3d thePts_;

			TColEntity_Ary1dOfTetrahedronIndex theV_;
			TColEntity_Ary1dOfTetrahedronIndex theE_;

		public:

			DelTri3d();

			DelTri3d(const TColGeom_Ary1dOfPnt3d& Points);

			Standard_Integer NbPoints() const;

			Standard_Integer NbTetrahedrons() const;

			const TColGeom_Ary1dOfPnt3d& Coords() const;

			const TColEntity_Ary1dOfTetrahedronIndex& Tetrahedrons() const;

			const TColEntity_Ary1dOfTetrahedronIndex& Neighbors() const;

			void Import(const TColGeom_Ary1dOfPnt3d& Points);

			void Perform();

			void ExportToPlt(fstream& File) const;
		};
	}
}

#include <DelTri3dI.hxx>

#endif // !_DelTri3d_Header
