#pragma once
#ifndef _Mesh3d_CycleInfo_Header
#define _Mesh3d_CycleInfo_Header

#include <Mesh3d_AftType.hxx>
#include <Mesh3d_PointCondition.hxx>
#include <Mesh3d_Node.hxx>
#include <Mesh3d_Edge.hxx>
#include <Mesh3d_Facet.hxx>
#include <Mesh3d_Element.hxx>
#include <TColMesh3d_HAry1dOfNode.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_CycleInfo
		{

		private:

			Global_Handle(Mesh3d_Node) theCreated_;
			Global_Handle(Mesh3d_Node) theValid_;

			Standard_Boolean IsAppendNewPoint_;   // true if the new Node appended to the candidate list

			Mesh3d_PointCondition theNewPointCondition_;

			Mesh3d_AftType theType_;

			Standard_Real theElementSize_;
			Standard_Real theSearchingRadius_;
			Standard_Real theSearchingRadius1_;
			Standard_Real theSearchingRadius2_;
			Standard_Real theMinDistance_;
			Standard_Real theMinEdgeDistance_;

			Geom_Pnt3d theCoord_;

			Global_Handle(Mesh3d_Facet) theCurrent_;

			TColMesh3d_HAry1dOfNode theNeighbors0_;
			TColMesh3d_HAry1dOfNode theNeighbors1_;
			TColMesh3d_HAry1dOfNode theNeighbors2_;

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

			Mesh3d_CycleInfo();

			Global_Handle(Mesh3d_Node) CreatedNode() const;

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

			Global_Handle(Mesh3d_Node)& CreatedNode();

			Global_Handle(Mesh3d_Facet)& Current();

			TColMesh3d_HAry1dOfNode& Neighbors0();

			TColMesh3d_HAry1dOfNode& Neighbors1();

			TColMesh3d_HAry1dOfNode& Neighbors2();

			const TColMesh3d_HAry1dOfNode& Neighbors0() const;

			const TColMesh3d_HAry1dOfNode& Neighbors1() const;

			const TColMesh3d_HAry1dOfNode& Neighbors2() const;

			const Mesh3d_PointCondition& Condition() const;

			const Mesh3d_AftType& Type() const;

			const Geom_Pnt3d& Coord() const;

			Standard_Real ElementSize() const;

			Standard_Real SearchRadius() const;

			Standard_Real SearchRadiusLevel1() const;

			Standard_Real SearchRadiusLevel2() const;

			Standard_Real MinDistanceFactor() const;

			Standard_Real MinEdgeDistanceFactor() const;

			Standard_Boolean IsAppended() const;

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

			void SetCreatedNode(Global_Handle(Mesh3d_Node) Node);

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

			void SetCondition(Mesh3d_PointCondition Condition);

			void SetType(Mesh3d_AftType Type);

			void SetCoord(Geom_Pnt3d & Coord);

			//! Throw an exception if ElementSize<=0
			void SetElementSize(const Standard_Real ElementSize);

			//! Throw an exception if Searching Radius <= 0
			void SetSearchingRadius(const Standard_Real SearchingRadius);

			//! Throw an exception if Searching Radius <= 0
			void SetSearchingRadiusLevel1(const Standard_Real SearchingRadius);

			//! Throw an exception if Searching Radius <= 0
			void SetSearchingRadiusLevel2(const Standard_Real SearchingRadius);

			void SetMinDistanceFactor(const Standard_Real MinDistanceFactor);

			void SetAppendedCondition(const Standard_Boolean AppendedCondition);

			void Reset();
		};
	}
}

#include <Mesh3d_CycleInfoI.hxx>

#endif // !_Mesh3d_CycleInfo_Header
