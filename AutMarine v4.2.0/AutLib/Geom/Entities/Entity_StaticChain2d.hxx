#pragma once
#ifndef _Entity_StaticChain2d_Header
#define _Entity_StaticChain2d_Header

#include <Global_Memory.hxx>
#include <Global_Debug.hxx>
#include <Standard_Stream.hxx>
#include <TColStd_Ary1dOfReal.hxx>
#include <TColGeom_Ary1dOfPnt2d.hxx>
#include <TColEntity_Ary1dOfEdgeIndex.hxx>
#include <TColEntity_Ary1dOfTriangleIndex.hxx>

namespace AutLib
{
	namespace GeoLib
	{
		class Entity_Box2d;

		class Entity_StaticChain2d
		{

		private:

			TColGeom_Ary1dOfPnt2d thePts_;
			TColEntity_Ary1dOfEdgeIndex theEdges_;

			Standard_Boolean IsCycle_;

		public:

			Entity_StaticChain2d();

			Entity_StaticChain2d(const TColGeom_Ary1dOfPnt2d& Points, const TColEntity_Ary1dOfEdgeIndex& Edges, const Standard_Boolean Cycle = Standard_False);

			//void Init(const TColGeom_Ary1dOfPnt2d& Points, const Standard_Boolean Cycle = Standard_False);

			void Init(const TColGeom_Ary1dOfPnt2d& Points, const TColEntity_Ary1dOfEdgeIndex& Edges, const Standard_Boolean Cycle = Standard_False);

			Standard_Integer NbPoints() const;

			Standard_Integer NbEdges() const;

			TColGeom_Ary1dOfPnt2d& Coords();

			TColEntity_Ary1dOfEdgeIndex& Edges();

			TColEntity_Ary1dOfTriangleIndex GetTriangleIndices() const;

			const TColGeom_Ary1dOfPnt2d& Coords() const;

			const TColEntity_Ary1dOfEdgeIndex& Edges() const;

			const Geom_Pnt2d& Coord(const Standard_Integer Index) const;

			const Entity_EdgeIndex& Edge(const Standard_Integer Index) const;

			Standard_Boolean IsCycle() const;

			Entity_Box2d BoundingBox() const;

			Entity_StaticChain2d Merged(const Standard_Real Resolution = 1.0E-3, const Standard_Real Radius = 1.0E-6) const;

			void Reverse();

			//! WARNING: This is a VERY SIMPLE Algorithm that not support the concave types.
			//Geom_StaticChain2d OffSet(const Standard_Real r, const Standard_Boolean Sense = Standard_False) const;

			void SetCoords(const TColGeom_Ary1dOfPnt2d& Points);

			void SetEdges(const TColEntity_Ary1dOfEdgeIndex& Edges);

			void SetCycle(const Standard_Boolean Cycle);

			void Merging(const Standard_Boolean HandleDegeneracy = Standard_True, const Standard_Real Resolution = 1.0E-3, const Standard_Real Radius = 1.0E-6);

			void ExportToPlt(fstream& File) const;
		};
	}
}

#include <Entity_StaticChain2dI.hxx>

#endif // !_Entity_StaticChain2d_Header
