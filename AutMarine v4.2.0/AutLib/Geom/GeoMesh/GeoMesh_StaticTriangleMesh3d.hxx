#pragma once
#ifndef _GeoMesh_StaticTriangleMesh3d_Header
#define _GeoMesh_StaticTriangleMesh3d_Header

#include <Entity_Triangulation3d.hxx>
#include <TColEntity_Ary1dOfEdgeIndex.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class GeoMesh_StaticTriangleMesh3d : public Entity_Triangulation3d
		{

		private:

			TColEntity_Ary1dOfEdgeIndex theEdges_;

			TColEntity_Ary1dOfTriangleIndex theEdgesOfTriangles_;

		public:

			GeoMesh_StaticTriangleMesh3d();

			GeoMesh_StaticTriangleMesh3d(const Entity_Triangulation3d& theTriangulation);

			GeoMesh_StaticTriangleMesh3d(const TColGeom_Ary1dOfPnt3d& theCoord, const TColEntity_Ary1dOfTriangleIndex& theElements);

			Standard_Integer NbEdges() const;

			const TColEntity_Ary1dOfEdgeIndex& Edges() const;

			const Entity_EdgeIndex& Edge(const Standard_Integer Index) const;

			const Entity_TriangleIndex& EdgesInTriangle(const Standard_Integer Index) const;

		private:

			void CreateEdges();

		};
	}
}

#include <GeoMesh_StaticTriangleMesh3dI.hxx>

#endif // !_GeoMesh_StaticTriangleMesh3d_Header
