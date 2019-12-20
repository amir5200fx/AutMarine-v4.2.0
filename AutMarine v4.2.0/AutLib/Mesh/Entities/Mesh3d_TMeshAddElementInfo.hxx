#pragma once
#ifndef _Mesh3d_TMeshAddElementInfo_Header
#define _Mesh3d_TMeshAddElementInfo_Header

#include <Global_Memory.hxx>
#include <Standard_TypeDef.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_Node;
		class Mesh3d_Edge;
		class Mesh3d_Facet;
		class Mesh3d_Element;

		class Mesh3d_TMeshAddElementInfo
		{

		private:

			Global_Handle(Mesh3d_Node) theValid_;

			Global_Handle(Mesh3d_Facet) theCurrent_;

			Global_Handle(Mesh3d_Facet) thePairedFacet0_;
			Global_Handle(Mesh3d_Facet) thePairedFacet1_;
			Global_Handle(Mesh3d_Facet) thePairedFacet2_;

			Global_Handle(Mesh3d_Edge) thePairedEdge3_;
			Global_Handle(Mesh3d_Edge) thePairedEdge4_;
			Global_Handle(Mesh3d_Edge) thePairedEdge5_;

			Global_Handle(Mesh3d_Facet) theCreatedFacet0_;
			Global_Handle(Mesh3d_Facet) theCreatedFacet1_;
			Global_Handle(Mesh3d_Facet) theCreatedFacet2_;

			Global_Handle(Mesh3d_Edge) theCreatedEdge3_;
			Global_Handle(Mesh3d_Edge) theCreatedEdge4_;
			Global_Handle(Mesh3d_Edge) theCreatedEdge5_;

			Global_Handle(Mesh3d_Element) theCreatedElement_;

		public:

			Mesh3d_TMeshAddElementInfo();

			Global_Handle(Mesh3d_Node) ValidNode() const;

			Global_Handle(Mesh3d_Facet) Current() const;

			Global_Handle(Mesh3d_Facet) PairedFacet0() const;

			Global_Handle(Mesh3d_Facet) PairedFacet1() const;

			Global_Handle(Mesh3d_Facet) PairedFacet2() const;

			Global_Handle(Mesh3d_Facet) CreatedFacet0() const;

			Global_Handle(Mesh3d_Facet) CreatedFacet1() const;

			Global_Handle(Mesh3d_Facet) CreatedFacet2() const;

			Global_Handle(Mesh3d_Edge) PairedEdge3() const;

			Global_Handle(Mesh3d_Edge) PairedEdge4() const;

			Global_Handle(Mesh3d_Edge) PairedEdge5() const;

			Global_Handle(Mesh3d_Edge) CreatedEdge3() const;

			Global_Handle(Mesh3d_Edge) CreatedEdge4() const;

			Global_Handle(Mesh3d_Edge) CreatedEdge5() const;

			Global_Handle(Mesh3d_Element) CreatedElement() const;

			Standard_Boolean IsPairedFacet0() const;

			Standard_Boolean IsPairedFacet1() const;

			Standard_Boolean IsPairedFacet2() const;

			Standard_Boolean IsCreatedFacet0() const;

			Standard_Boolean IsCreatedFacet1() const;

			Standard_Boolean IsCreatedFacet2() const;

			Standard_Boolean IsPairedEdge3() const;

			Standard_Boolean IsPairedEdge4() const;

			Standard_Boolean IsPairedEdge5() const;

			Standard_Boolean IsCreatedEdge3() const;

			Standard_Boolean IsCreatedEdge4() const;

			Standard_Boolean IsCreatedEdge5() const;

			void SetValidNode(Global_Handle(Mesh3d_Node) Node);

			void SetCurrent(Global_Handle(Mesh3d_Facet) Facet);

			void SetPairedFacet0(Global_Handle(Mesh3d_Facet) Facet);

			void SetPairedFacet1(Global_Handle(Mesh3d_Facet) Facet);

			void SetPairedFacet2(Global_Handle(Mesh3d_Facet) Facet);

			void SetCreatedFacet0(Global_Handle(Mesh3d_Facet) Facet);

			void SetCreatedFacet1(Global_Handle(Mesh3d_Facet) Facet);

			void SetCreatedFacet2(Global_Handle(Mesh3d_Facet) Facet);

			void SetPairedEdge3(Global_Handle(Mesh3d_Edge) Edge);

			void SetPairedEdge4(Global_Handle(Mesh3d_Edge) Edge);

			void SetPairedEdge5(Global_Handle(Mesh3d_Edge) Edge);

			void SetCreatedEdge3(Global_Handle(Mesh3d_Edge) Edge);

			void SetCreatedEdge4(Global_Handle(Mesh3d_Edge) Edge);

			void SetCreatedEdge5(Global_Handle(Mesh3d_Edge) Edge);

			void SetCreatedElement(Global_Handle(Mesh3d_Element) Element);

			void Reset();
		};
	}
}

#include <Mesh3d_TMeshAddElementInfoI.hxx>

#endif // !_Mesh3d_TMeshAddElementInfo_Header
