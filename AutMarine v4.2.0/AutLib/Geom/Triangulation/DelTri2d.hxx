#pragma once
#ifndef _DelTri2d_Header
#define _DelTri2d_Header

#include <Geom_Pnt2d.hxx>
#include <Entity_TriangleIndex.hxx>
#include <TColGeom_Ary1dOfPnt2d.hxx>
#include <TColEntity_Ary1dOfTriangleIndex.hxx>
#include <Standard_Stream.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class DelTri2d
		{

		private:

			TColEntity_Ary1dOfTriangleIndex theV_;
			TColEntity_Ary1dOfTriangleIndex theE_;

			TColGeom_Ary1dOfPnt2d thePts_;

			Standard_Integer theNbPts_;
			Standard_Integer theNbTris_;

		public:

			DelTri2d(const TColGeom_Ary1dOfPnt2d& Points);

			const Entity_TriangleIndex & Vertex(const Standard_Integer Index) const;

			const Entity_TriangleIndex & Neighbor(const Standard_Integer Index) const;

			const TColEntity_Ary1dOfTriangleIndex& Vertices() const;

			const TColEntity_Ary1dOfTriangleIndex& Neighbors() const;

			Standard_Integer NbElements() const;

			void Perform();

			void Plot(fstream& File) const;

		private:

			Standard_Integer Edge(const Standard_Integer L, const Standard_Integer K) const;

			Standard_Integer TriLoc(const Geom_Pnt2d& Pt) const;

			Standard_Integer TriLoc(const Geom_Pnt2d& Pt, const Standard_Integer t) const;

			Standard_Boolean Swap(const Geom_Pnt2d& Pt, const Geom_Pnt2d& P1, const Geom_Pnt2d& P2, const Geom_Pnt2d& P3) const;

			Standard_Boolean IsRightSide(const Geom_Pnt2d& Pt, const Geom_Pnt2d& P1, const Geom_Pnt2d& P2) const;

			void Delaunay();
		};
	}
}

#include <DelTri2dI.hxx>

#endif // !_DelTri2d_Header
