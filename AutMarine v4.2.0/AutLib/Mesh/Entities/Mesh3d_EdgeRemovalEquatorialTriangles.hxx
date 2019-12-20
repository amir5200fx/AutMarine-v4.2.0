#pragma once
#ifndef _Mesh3d_EdgeRemovalEquatorialTriangles_Header
#define _Mesh3d_EdgeRemovalEquatorialTriangles_Header

#include <TColMesh3d_HAry1dOfEdge.hxx>
#include <TColMesh3d_HAry1dOfNode.hxx>
#include <TColEntity_Ary1dOfTriangleIndex.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_EdgeRemovalEquatorialTriangles
		{

		private:

			TColMesh3d_HAry1dOfEdge theEdges_;

			TColMesh3d_HAry1dOfNode theNodes_;

			TColEntity_Ary1dOfTriangleIndex theTriangles_;

			Standard_Real theWorstQuality_;

		protected:

			Mesh3d_EdgeRemovalEquatorialTriangles();

			Mesh3d_EdgeRemovalEquatorialTriangles(const TColMesh3d_HAry1dOfNode& theNodes, const TColMesh3d_HAry1dOfEdge& theEdges, const TColEntity_Ary1dOfTriangleIndex& theTriangles);

		public:

			virtual ~Mesh3d_EdgeRemovalEquatorialTriangles();

			void Init(const TColMesh3d_HAry1dOfNode& theNodes, const TColMesh3d_HAry1dOfEdge& theEdges, const TColEntity_Ary1dOfTriangleIndex& theTriangles);

			const TColMesh3d_HAry1dOfNode& Nodes() const;

			const TColMesh3d_HAry1dOfEdge& Edges() const;

			const TColEntity_Ary1dOfTriangleIndex& Triangles() const;

			Standard_Real WorstQuality() const;

			void SetWorstQuality(const Standard_Real theWorstQuality);

			void ExportToPlt(fstream& File) const;
		};
	}
}

#include <Mesh3d_EdgeRemovalEquatorialTrianglesI.hxx>

#endif // !_Mesh3d_EdgeRemovalEquatorialTriangles_Header
