#pragma once
#ifndef _Mesh2d_TMeshAddElementInfo_Header
#define _Mesh2d_TMeshAddElementInfo_Header

#include <Global_Memory.hxx>
#include <Standard_TypeDef.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh2d_Node;
		class Mesh2d_Edge;
		class Mesh2d_Element;

		class Mesh2d_TMeshAddElementInfo
		{

		private:

			Global_Handle(Mesh2d_Node) theValid_;

			Global_Handle(Mesh2d_Edge) theCurrent_;

			Global_Handle(Mesh2d_Edge) thePairedEdge0_;
			Global_Handle(Mesh2d_Edge) thePairedEdge1_;

			Global_Handle(Mesh2d_Edge) theCreatedEdge0_;
			Global_Handle(Mesh2d_Edge) theCreatedEdge1_;

			Global_Handle(Mesh2d_Element) theCreatedElement_;

		public:

			Mesh2d_TMeshAddElementInfo();

			Global_Handle(Mesh2d_Node) ValidNode() const;

			Global_Handle(Mesh2d_Edge) Current() const;

			Global_Handle(Mesh2d_Edge) PairedEdge0() const;

			Global_Handle(Mesh2d_Edge) PairedEdge1() const;

			Global_Handle(Mesh2d_Edge) CreatedEdge0() const;

			Global_Handle(Mesh2d_Edge) CreatedEdge1() const;

			Global_Handle(Mesh2d_Element) CreatedElement() const;

			Standard_Boolean IsPairedEdge0() const;

			Standard_Boolean IsPairedEdge1() const;

			Standard_Boolean IsCreatedEdge0() const;

			Standard_Boolean IsCreatedEdge1() const;

			void SetValidNode(Global_Handle(Mesh2d_Node) Node);

			void SetCurrent(Global_Handle(Mesh2d_Edge) Edge);

			void SetPairedEdge0(Global_Handle(Mesh2d_Edge) Edge);

			void SetPairedEdge1(Global_Handle(Mesh2d_Edge) Edge);

			void SetCreatedEdge0(Global_Handle(Mesh2d_Edge) Edge);

			void SetCreatedEdge1(Global_Handle(Mesh2d_Edge) Edge);

			void SetCreatedElement(Global_Handle(Mesh2d_Element) Element);

			void Reset();
		};
	}
}

#include <Mesh2d_TMeshAddElementInfoI.hxx>

#endif // !_Mesh2d_TMeshAddElementInfo_Header
