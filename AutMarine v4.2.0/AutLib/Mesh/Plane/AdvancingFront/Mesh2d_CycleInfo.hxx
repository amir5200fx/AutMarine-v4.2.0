#pragma once
#ifndef _Mesh2d_CycleInfo_Header
#define _Mesh2d_CycleInfo_Header

#include <Mesh2d_AftType.hxx>
#include <Mesh2d_PointCondition.hxx>
#include <Mesh2d_Node.hxx>
#include <Mesh2d_Edge.hxx>
#include <Mesh2d_Element.hxx>
#include <TColMesh2d_HAry1dOfNode.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh2d_CycleInfo
		{

		private:

			Global_Handle(Mesh2d_Node) theCreated_;
			Global_Handle(Mesh2d_Node) theValid_;

			Standard_Boolean IsAppendNewPoint_;   // true if the new Node appended to the candidate list

			Mesh2d_PointCondition theNewPointCondition_;

			Mesh2d_AftType theType_;

			Standard_Real theElementSize_;
			Standard_Real theSearchingRadius_;
			Standard_Real theSearchingRadius1_;
			Standard_Real theSearchingRadius2_;
			Standard_Real theMinDistance_;

			Geom_Pnt2d theCoord_;

			Global_Handle(Mesh2d_Edge) theCurrent_;

			/*TColMesh3d_HAry1dOfNode theNeighbors0_;
			TColMesh3d_HAry1dOfNode theNeighbors1_;
			TColMesh3d_HAry1dOfNode theNeighbors2_;*/

			Global_Handle(Mesh2d_Edge) thePairedEdge0_;
			Global_Handle(Mesh2d_Edge) thePairedEdge1_;

			Global_Handle(Mesh2d_Edge) theCreatedEdge0_;
			Global_Handle(Mesh2d_Edge) theCreatedEdge1_;

			Global_Handle(Mesh2d_Element) theCreatedElement_;

		public:

			Mesh2d_CycleInfo();

			Global_Handle(Mesh2d_Node) CreatedNode() const;

			Global_Handle(Mesh2d_Node) ValidNode() const;

			Global_Handle(Mesh2d_Edge) Current() const;

			Global_Handle(Mesh2d_Edge) PairedEdge0() const;

			Global_Handle(Mesh2d_Edge) PairedEdge1() const;

			Global_Handle(Mesh2d_Edge) CreatedEdge0() const;

			Global_Handle(Mesh2d_Edge) CreatedEdge1() const;

			Global_Handle(Mesh2d_Element) CreatedElement() const;

			Global_Handle(Mesh2d_Node)& CreatedNode();

			Global_Handle(Mesh2d_Edge)& Current();

			const Mesh2d_PointCondition& Condition() const;

			const Mesh2d_AftType& Type() const;

			const Geom_Pnt2d& Coord() const;

			Standard_Real ElementSize() const;

			Standard_Real SearchRadius() const;

			Standard_Real SearchRadiusLevel1() const;

			Standard_Real SearchRadiusLevel2() const;

			Standard_Real MinDistanceFactor() const;

			Standard_Boolean IsAppended() const;

			Standard_Boolean IsPairedEdge0() const;

			Standard_Boolean IsPairedEdge1() const;

			Standard_Boolean IsCreatedEdge0() const;

			Standard_Boolean IsCreatedEdge1() const;

			void SetCreatedNode(Global_Handle(Mesh2d_Node) Node);

			void SetValidNode(Global_Handle(Mesh2d_Node) Node);

			void SetCurrent(Global_Handle(Mesh2d_Edge) Edge);

			void SetPairedEdge0(Global_Handle(Mesh2d_Edge) Edge);

			void SetPairedEdge1(Global_Handle(Mesh2d_Edge) Edge);

			void SetCreatedEdge0(Global_Handle(Mesh2d_Edge) Edge);

			void SetCreatedEdge1(Global_Handle(Mesh2d_Edge) Edge);

			void SetCreatedElement(Global_Handle(Mesh2d_Element) Element);

			void SetCondition(Mesh2d_PointCondition Condition);

			void SetType(Mesh2d_AftType Type);

			void SetCoord(Geom_Pnt2d & Coord);

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

#include <Mesh2d_CycleInfoI.hxx>

#endif // !_Mesh2d_CycleInfo_Header
