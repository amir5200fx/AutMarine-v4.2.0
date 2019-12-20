#pragma once
#ifndef _Mesh2d_Edge_Header
#define _Mesh2d_Edge_Header

#include <Mesh2d_Node.hxx>
#include <Entity_EdgeIndex.hxx>
#include <TColMesh2d_HAry1dOfNode.hxx>

namespace AutLib
{
	namespace MeshLib
	{
		
		class Mesh2d_Edge
		{

		private:

			Global_Handle(Mesh2d_Node) theNodes_[2];

			Geom_Pnt2d theCentre_;

			Standard_Integer theIndex_;

			Standard_Real theLength_;

			Standard_Boolean IsCavity_;

			Global_Handle(Mesh2d_Element) theRight_;
			Global_Handle(Mesh2d_Element) theLeft_;

		public:

			Mesh2d_Edge();

			Mesh2d_Edge(const Standard_Integer Index, const Standard_Real Length, const Geom_Pnt2d& Centre, Global_Handle(Mesh2d_Node) Node0, Global_Handle(Mesh2d_Node) Node1);

			virtual ~Mesh2d_Edge();

			Standard_Integer Index() const;

			Standard_Real Length() const;

			Standard_Real SearchRadius() const;

			Standard_Real MaxAdjastedLength() const;

			Standard_Boolean IsCavity() const;

			Standard_Boolean IsOnFront() const;

			Standard_Boolean IsOrphan() const;

			Standard_Integer NbElements() const;

			Global_Handle(Mesh2d_Node) Node0() const;

			Global_Handle(Mesh2d_Node) Node1() const;

			Global_Handle(Mesh2d_Node) Node(const Standard_Integer Index) const;

			Global_Handle(Mesh2d_Node)& Node(const Standard_Integer Index);

			Global_Handle(Mesh2d_Element) RightElement() const;

			Global_Handle(Mesh2d_Element) LeftElement() const;

			const Geom_Pnt2d& Centre() const;

			void Reverse();

			void SetIndex(const Standard_Integer Index);

			void SetLength(const Standard_Real Length);

			void SetCavity(const Standard_Boolean Cavity);

			void SetNode(const Standard_Integer Index, Global_Handle(Mesh2d_Node) Node);

			void SetLeftElement(Global_Handle(Mesh2d_Element) Element);

			void SetRightElement(Global_Handle(Mesh2d_Element) Element);

			void SetCentre(const Geom_Pnt2d& Coord);

			//! Throw an exception if not found the element
			void RemoveFromElements(Global_Handle(Mesh2d_Element) Element);
		};
	}
}

using AutLib::MeshLib::Mesh2d_Edge;

#include <Mesh2d_EdgeI.hxx>

#endif // !_Mesh2d_Edge_Header
