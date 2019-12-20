#pragma once
#ifndef _Entity_Triangulation2d_Header
#define _Entity_Triangulation2d_Header

#include <TColEntity_Ary1dOfTriangleIndex.hxx>
#include <TColGeom_Ary1dOfPnt2d.hxx>

namespace AutLib
{
	class Primitive_Field;

	namespace GeoLib
	{


		class Entity_Triangulation2d
		{

		protected:

			TColGeom_Ary1dOfPnt2d thePoints_;

			TColEntity_Ary1dOfTriangleIndex theTriangles_;

		public:

			Entity_Triangulation2d();

			Entity_Triangulation2d(const TColGeom_Ary1dOfPnt2d& Coords, const TColEntity_Ary1dOfTriangleIndex& Triangles);

			Standard_Integer NbPoints() const;

			Standard_Integer NbTriangles() const;

			const TColGeom_Ary1dOfPnt2d& Points() const;

			TColGeom_Ary1dOfPnt2d& Points();

			const TColEntity_Ary1dOfTriangleIndex& Triangles() const;

			TColEntity_Ary1dOfTriangleIndex& Triangles();

			void ExportToPlt(fstream& File) const;

			//! Throw an exception if the Field is not compatible with the Mesh
			void ExportToPlt(const Primitive_Field& Field, fstream& File) const;

		};
	}
}

#include <Entity_Triangulation2dI.hxx>

#endif // !_Entity_Triangulation2d_Header
