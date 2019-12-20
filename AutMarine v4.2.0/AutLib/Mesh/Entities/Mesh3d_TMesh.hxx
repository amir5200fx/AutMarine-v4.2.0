#pragma once
#ifndef _Mesh3d_TMesh_Header
#define _Mesh3d_TMesh_Header

#include <Mesh3d_Mesh.hxx>
#include <Mesh3d_Element.hxx>
#include <Mesh3d_TMeshAddElementInfo.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_SizeMap;

		class Mesh3d_TMesh : public Mesh3d_Mesh
		{

			friend class Mesh3d_Optimization;

		private:

			Mesh3d_TMeshAddElementInfo theInfo_;

		public:

			Mesh3d_TMesh();

			~Mesh3d_TMesh();

			Global_Handle(Mesh3d_Element) AddToTopology(Global_Handle(Mesh3d_Facet) theFront, Global_Handle(Mesh3d_Node) theNode, const Mesh3d_SizeMap& theSizeMap, const Standard_Boolean RemoveFromFront = Standard_True);

			void ForcedToRemoveFromTopology(Global_Handle(Mesh3d_Edge) theEdge, const Standard_Boolean BoundaryChecking = Standard_True);

			void ForcedToRemoveFromTopology(Global_Handle(Mesh3d_Facet) theFacet, const Standard_Boolean BoundaryChecking = Standard_True);

			void RemoveFromTopology(Global_Handle(Mesh3d_Element) theElement, TColMesh3d_HAry1dOfFacet& theRetrievedFacets, TColMesh3d_HAry1dOfEdge& theRetrievedEdges, TColMesh3d_HAry1dOfNode& theRetrievedNodes, TColMesh3d_HAry1dOfFacet& theRemovedFacets, TColMesh3d_HAry1dOfEdge& theRemovedEdges, TColMesh3d_HAry1dOfNode& theRemovedNodes, const Standard_Boolean BoundaryChecking = Standard_True);

			void RemoveFromTopology(Global_Handle(Mesh3d_Element) theElement, Standard_Boolean BoundaryChecking = Standard_True);

			//! Throw an exception if duplicate data detected
			void AttachToMeshNodes(Global_Handle(Mesh3d_Element) Element);

			//! Throw an exception if duplicate data detected
			void AttachToMeshNodes(Global_Handle(Mesh3d_Facet) Facet);

			//! Throw an exception if duplicate data detected
			void AttachToMeshNodes(Global_Handle(Mesh3d_Edge) Edge);

			//! Throw an exception if duplicate data detected
			void AttachToMeshEdges(Global_Handle(Mesh3d_Element) Element);

			//! Throw an exception if duplicate data detected
			void AttachToMeshEdges(Global_Handle(Mesh3d_Facet) Facet);

			//! Throw an exception if duplicate data detected
			void AttachToFrontNodes(Global_Handle(Mesh3d_Facet) Facet);

			//! Throw an exception if duplicate data detected
			void AttachToFrontNodes(Global_Handle(Mesh3d_Edge) Edge);

			//! Throw an exception if duplicate data detected
			void AttachToFrontEdges(Global_Handle(Mesh3d_Facet) Facet);

			//! Throw an exception if duplicate data detected
			void AttachToFront(Global_Handle(Mesh3d_Facet) Facet);

			//! Throw an exception if duplicate data detected
			void AttachToMesh(Global_Handle(Mesh3d_Facet) Facet);

			void deAttachFromMesh(Global_Handle(Mesh3d_Element) Element);

			void deAttachFromMesh(Global_Handle(Mesh3d_Facet) Facet);

			void deAttachFromMesh(Global_Handle(Mesh3d_Edge) Edge);

			void deAttachFromFront(Global_Handle(Mesh3d_Facet) Facet);

			void deAttachFromFront(Global_Handle(Mesh3d_Edge) Edge);

		private:

			void RemoveFromTopology(Global_Handle(Mesh3d_Facet) theFacet, const Standard_Boolean BoundaryCheck);

			void RemoveFromTopology(Global_Handle(Mesh3d_Edge) theEdge, const Standard_Boolean BoundaryCheck);

			void SetPairedEdges();

			void SetPairedFacets();

			void UpdateEdges(const Mesh3d_SizeMap& theSizeMap);

			void UpdateFacets(const Mesh3d_SizeMap& theSizeMap);

			void CreateElement();

			void UpdateElement();

			void CalcGeometryOf(Mesh3d_Facet & theFacet, const Mesh3d_SizeMap& theSizeMap) const;

			void UpdateMaxLength(const Standard_Real theLength, Mesh3d_Edge & theEdge);
		};
	}
}

#include <Mesh3d_TMeshI.hxx>

#endif // !_Mesh3d_TMesh_Header
