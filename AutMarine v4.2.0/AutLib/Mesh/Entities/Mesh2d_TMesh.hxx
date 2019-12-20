#pragma once
#ifndef _Mesh2d_TMesh_Header
#define _Mesh2d_TMesh_Header

#include <Mesh2d_Mesh.hxx>
#include <Mesh2d_Edge.hxx>
#include <Mesh2d_Element.hxx>
#include <Mesh2d_TMeshAddElementInfo.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh2d_TMesh : public Mesh2d_Mesh
		{

			friend class Mesh2d_Optimization;

		private:

			Mesh2d_TMeshAddElementInfo theInfo_;

		public:

			Mesh2d_TMesh();

			virtual ~Mesh2d_TMesh();

			Global_Handle(Mesh2d_Element) AddToTopology(Global_Handle(Mesh2d_Edge) theFront, Global_Handle(Mesh2d_Node) theNode, const Mesh2d_SizeMap& theSizeMap, const Standard_Boolean RemoveFromFront = Standard_True);

			void ForcedToRemoveFromTopology(Global_Handle(Mesh2d_Edge) theEdge, const Standard_Boolean BoundaryChecking = Standard_True);

			void RemoveFromTopology(Global_Handle(Mesh2d_Element) theElement, TColMesh2d_HAry1dOfEdge& theRetrievedEdges, TColMesh2d_HAry1dOfNode& theRetrievedNodes, TColMesh2d_HAry1dOfEdge& theRemovedEdges, TColMesh2d_HAry1dOfNode& theRemovedNodes, const Standard_Boolean BoundaryChecking = Standard_True);

			//! Throw an exception if duplicate data detected
			void AttachToMeshNodes(Global_Handle(Mesh2d_Element) Element);

			//! Throw an exception if duplicate data detected
			void AttachToMeshNodes(Global_Handle(Mesh2d_Edge) Edge);

			//! Throw an exception if duplicate data detected
			//void AttachToMeshEdges(Global_Handle(Mesh2d_Element) Element);

			//! Throw an exception if duplicate data detected
			void AttachToFrontNodes(Global_Handle(Mesh2d_Edge) Edge);

			void deAttachFromMesh(Global_Handle(Mesh2d_Element) Element);

			void deAttachFromMesh(Global_Handle(Mesh2d_Edge) Edge);

			void deAttachFromFront(Global_Handle(Mesh2d_Edge) Edge);

		private:

			void RemoveFromTopology(Global_Handle(Mesh2d_Edge) theEdge, const Standard_Boolean BoundaryCheck);

			void SetPairedEdges();

			void UpdateEdges(const Mesh2d_SizeMap& theSizeMap);

			void CreateElement();

			void UpdateElement();

			void UpdateMaxLength(const Standard_Real theLength, Mesh2d_Edge & theEdge);
		};
	}
}

#include <Mesh2d_TMeshI.hxx>

#endif // !_Mesh2d_TMesh_Header
