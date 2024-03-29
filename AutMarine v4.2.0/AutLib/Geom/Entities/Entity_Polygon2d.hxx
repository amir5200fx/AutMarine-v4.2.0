#pragma once
#ifndef _Entity_Polygon2d_Header
#define _Entity_Polygon2d_Header

#include <TColGeom_Ary1dOfPnt2d.hxx>
#include <Standard_Stream.hxx>

namespace AutLib
{
	class Primitive_Field;

	namespace GeoLib
	{

		class Entity_Polygon2d
		{

		protected:

			TColGeom_Ary1dOfPnt2d thePoints_;

			Standard_Real theDeflection_;

		public:

			Entity_Polygon2d();

			//! Constructs a 2D polygon defined by the table of points
			Entity_Polygon2d(const TColGeom_Ary1dOfPnt2d& Points);

			void Init(const TColGeom_Ary1dOfPnt2d& Points);

			//! Returns the deflection of this polygon.
			//! Deflection is used in cases where the polygon is an
			//! approximate representation of a curve. Deflection
			//! represents the maximum distance permitted between any
			//! point on the curve and the corresponding point on the polygon.
			//! By default the deflection value is equal to 0. An algorithm
			//! using this 2D polygon with a deflection value equal to 0
			//! considers that it is working with a true polygon and not with
			//! an approximate representation of a curve. The Deflection
			//! function is used to modify the deflection value of this polygon.
			//! The deflection value can be used by any algorithm working  with 2D polygons.
			//! For example:
			//! -   An algorithm may use a unique deflection value for all
			//! its polygons. In this case it is not necessary to use the
			//! Deflection function.
			//! -   Or an algorithm may want to attach a different
			//! deflection to each polygon. In this case, the Deflection
			//! function is used to set a value on each polygon, and
			//! later to fetch the value.
			Standard_Real Deflection() const;

			Entity_Polygon2d Reversed() const;

			//! Sets the deflection of this polygon to D
			void SetDeflection(const Standard_Real D);

			void SetCoords(const TColGeom_Ary1dOfPnt2d& Points);

			void Reverse();

			void Smoothing(const Standard_Real Omega, const Standard_Integer NbIterations);

			//! Returns the number of nodes in this polygon.
			//! Note: If the polygon is closed, the point of closure is
			//! repeated at the end of its table of nodes. Thus, on a closed
			//! triangle, the function NbNodes returns 4.
			Standard_Integer NbPoints() const;

			Standard_Boolean IsClosed() const;

			TColGeom_Ary1dOfPnt2d& Points();

			Geom_Pnt2d Point(const Standard_Integer theIndex) const;

			const TColGeom_Ary1dOfPnt2d& Points() const;

			void ExportToPlt(fstream& File) const;

			void ExportToPlt(const Primitive_Field& theField, fstream& File) const;
		};
	}
}

#include <Entity_Polygon2dI.hxx>

#endif // !_Entity_Polygon2d_Header
