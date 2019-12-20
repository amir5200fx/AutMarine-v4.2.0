#pragma once
#ifndef _Mesh3d_MeshTools_Header
#define _Mesh3d_MeshTools_Header

#include <Mesh3d_Node.hxx>
#include <Mesh3d_Edge.hxx>
#include <TColMesh3d_HAry1dOfFacet.hxx>
#include <TColMesh3d_HAry1dOfElement.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_MeshTools
		{

		public:

			static Standard_Boolean CheckToInsertToMesh(Global_Handle(Mesh3d_Edge) theEdge);

			static Standard_Boolean CheckToInsertToMesh(Global_Handle(Mesh3d_Facet) theFacet);

			static Standard_Boolean CheckToInsertToMesh(Global_Handle(Mesh3d_Element) theElement);

			static Standard_Boolean CheckToInsertToFront(Global_Handle(Mesh3d_Edge) theEdge);

			static Standard_Boolean CheckToInsertToFront(Global_Handle(Mesh3d_Facet) theFacet);

			static Standard_Boolean CheckToRemoveFromMesh(Global_Handle(Mesh3d_Node) theNode);

			static Standard_Boolean CheckToRemoveFromMesh(Global_Handle(Mesh3d_Edge) theEdge);

			static Standard_Boolean CheckToRemoveFromMesh(Global_Handle(Mesh3d_Facet) theFacet);

			static Standard_Boolean CheckToRemoveFromMesh(Global_Handle(Mesh3d_Element) theElement);

			static Standard_Boolean CheckToRemoveFromFront(Global_Handle(Mesh3d_Node) theNode);

			static Standard_Boolean CheckToRemoveFromFront(Global_Handle(Mesh3d_Edge) theEdge);

			static Standard_Boolean CheckToRemoveFromFront(Global_Handle(Mesh3d_Facet) theFacet);

			static Standard_Boolean DeepCheckToConfirmFrontEntity(Global_Handle(Mesh3d_Facet) theFacet);

			static void IdentifyElementsAdjustedToFrontFacets(const TColMesh3d_HAry1dOfFacet& theFacets, TColMesh3d_HAry1dOfElement& theElements);
		};
	}
}

#endif // !_Mesh3d_MeshTools_Header
