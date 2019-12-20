#pragma once
#ifndef _Entity_Triangulation3d_Header
#define _Entity_Triangulation3d_Header

#include <TColEntity_Ary1dOfTriangleIndex.hxx>
#include <TColGeom_Ary1dOfPnt3d.hxx>

namespace AutLib
{
	namespace GeoLib
	{
		class Entity_Box3d;

		class Entity_Triangulation3d
		{

		protected:

			TColGeom_Ary1dOfPnt3d thePoints_;

			TColEntity_Ary1dOfTriangleIndex theTriangles_;

		public:

			Entity_Triangulation3d();

			Entity_Triangulation3d(const TColGeom_Ary1dOfPnt3d& Coords, const TColEntity_Ary1dOfTriangleIndex& Triangles);

			Standard_Integer NbPoints() const;

			Standard_Integer NbTriangles() const;

			const Entity_TriangleIndex& Triangle(const Standard_Integer Index) const;

			const TColGeom_Ary1dOfPnt3d& Points() const;

			TColGeom_Ary1dOfPnt3d& Points();

			const TColEntity_Ary1dOfTriangleIndex& Triangles() const;

			TColEntity_Ary1dOfTriangleIndex& Triangles();

			Entity_Box3d BoundingBox() const;

			void Reverse();

			void ImportFrom(fstream& File);

			void ExportTo(fstream& File) const;

			void ExportToPlt(fstream& File) const;

			void ExportNormalsToPlt(fstream& File) const;

		};
	}
}

#include <Entity_Triangulation3dI.hxx>

#endif // !_Entity_Triangulation3d_Header
