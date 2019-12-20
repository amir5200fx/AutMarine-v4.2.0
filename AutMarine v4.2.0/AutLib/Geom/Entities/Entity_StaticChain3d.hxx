#pragma once
#ifndef _Entity_StaticChain3d_Header
#define _Entity_StaticChain3d_Header

#include <TColGeom_Ary1dOfPnt3d.hxx>
#include <TColEntity_Ary1dOfEdgeIndex.hxx>
#include <TColEntity_Ary1dOfTriangleIndex.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Entity_StaticChain3d
		{

		private:

			TColGeom_Ary1dOfPnt3d thePts_;
			TColEntity_Ary1dOfEdgeIndex theEdges_;

			Standard_Boolean IsCycle_;

		public:

			Entity_StaticChain3d();

			void Init(const TColGeom_Ary1dOfPnt3d& Points, const TColEntity_Ary1dOfEdgeIndex& Edges, const Standard_Boolean Cycle = Standard_False);

			Standard_Integer NbPoints() const;

			Standard_Integer NbEdges() const;

			TColGeom_Ary1dOfPnt3d& Coords();

			TColEntity_Ary1dOfEdgeIndex& Edges();

			TColEntity_Ary1dOfTriangleIndex GetTriangleIndices() const;

			const TColGeom_Ary1dOfPnt3d& Coords() const;

			const TColEntity_Ary1dOfEdgeIndex& Edges() const;

			const Geom_Pnt3d& Coord(const Standard_Integer Index) const;

			const Entity_EdgeIndex& Edge(const Standard_Integer Index) const;

			Standard_Boolean IsCycle() const;

			Entity_StaticChain3d Merged(const Standard_Real Resolution = 1.0E-3, const Standard_Real Radius = 1.0E-6) const;

			void SetCoords(const TColGeom_Ary1dOfPnt3d& Points);

			void SetEdges(const TColEntity_Ary1dOfEdgeIndex& Edges);

			void SetCycle(const Standard_Boolean Cycle);

			void Merging(const Standard_Real Resolution = 1.0E-3, const Standard_Real Radius = 1.0E-6, const Standard_Boolean HandleDegeneracy = Standard_True);

			void ExportToPlt(fstream& File) const;
		};
	}
}

#include <Entity_StaticChain3dI.hxx>

#endif // !_Entity_StaticChain3d_Header
