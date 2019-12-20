#pragma once
#ifndef _Mesh3d_Facet_Header
#define _Mesh3d_Facet_Header

#include <Mesh3d_Edge.hxx>

namespace AutLib
{
	namespace MeshLib
	{
		
		class Mesh3d_Facet
		{

		private:

			Global_Handle(Mesh3d_Node) theNodes_[3];
			Global_Handle(Mesh3d_Edge) theEdges_[3];

			Standard_Integer theIndex_;

			Standard_Real theArea_;
			Standard_Real theLength_;

			Standard_Boolean IsCavity_;

			Geom_Pnt3d theCentre_;

			Global_Handle(Mesh3d_Element) theRightElement_;
			Global_Handle(Mesh3d_Element) theLeftElement_;

		public:

			Mesh3d_Facet();

			Mesh3d_Facet(const Standard_Integer Index);

			Mesh3d_Facet(const Standard_Integer Index, Global_Handle(Mesh3d_Node) theNode0, Global_Handle(Mesh3d_Node) theNode1, Global_Handle(Mesh3d_Node) theNode2);

			Mesh3d_Facet(const Standard_Integer Index, Global_Handle(Mesh3d_Node) theNode0, Global_Handle(Mesh3d_Node) theNode1, Global_Handle(Mesh3d_Node) theNode2, Global_Handle(Mesh3d_Edge) theEdge0, Global_Handle(Mesh3d_Edge) theEdge1, Global_Handle(Mesh3d_Edge) theEdge2);

			virtual ~Mesh3d_Facet();

			Global_Handle(Mesh3d_Node) Node0() const;

			Global_Handle(Mesh3d_Node) Node1() const;

			Global_Handle(Mesh3d_Node) Node2() const;

			Global_Handle(Mesh3d_Edge) Edge0() const;

			Global_Handle(Mesh3d_Edge) Edge1() const;

			Global_Handle(Mesh3d_Edge) Edge2() const;

			Global_Handle(Mesh3d_Element) RightElement() const;

			Global_Handle(Mesh3d_Element) LeftElement() const;

			Global_Handle(Mesh3d_Node) Node(const Standard_Integer Index) const;

			Global_Handle(Mesh3d_Node) OppositeNode(const Mesh3d_Edge& theEdge) const;

			Global_Handle(Mesh3d_Edge) Edge(const Standard_Integer Index) const;

			Standard_Integer Index() const;

			Standard_Integer OppositeNodeIndex(const Mesh3d_Edge& theEdge) const;

			Standard_Real Area() const;

			Standard_Real Length() const;

			Standard_Real MaxRadius() const;

			Standard_Boolean IsCavity() const;

			Standard_Boolean IsOnFront() const;

			Standard_Boolean IsOrphan() const;

			Standard_Boolean IsContain(Global_Handle(Mesh3d_Element) theElement) const;

			Geom_Pnt3d Normal() const;

			const Geom_Pnt3d& Centre() const;

			void SetIndex(const Standard_Integer Value);

			void SetNode0(Global_Handle(Mesh3d_Node) Node);

			void SetNode1(Global_Handle(Mesh3d_Node) Node);

			void SetNode2(Global_Handle(Mesh3d_Node) Node);

			void SetEdge0(Global_Handle(Mesh3d_Edge) Edge);

			void SetEdge1(Global_Handle(Mesh3d_Edge) Edge);

			void SetEdge2(Global_Handle(Mesh3d_Edge) Edge);

			void SetRightElement(Global_Handle(Mesh3d_Element) Element);

			void SetLeftElement(Global_Handle(Mesh3d_Element) Element);

			void SetNode(const Standard_Integer Index, Global_Handle(Mesh3d_Node) Node);

			void SetEdge(const Standard_Integer Index, Global_Handle(Mesh3d_Edge) Edge);

			void SetCentre(const Geom_Pnt3d& Coord);

			void SetLength(const Standard_Real Length);

			void SetArea(const Standard_Real theArea);

			void SetAsCavity();

			void SetAsNotCavity();

			void Reverse();
		};
	}
}

using AutLib::MeshLib::Mesh3d_Facet;

#include <Mesh3d_FacetI.hxx>

#endif // !_Mesh3d_Facet_Header
