#pragma once
#ifndef _SubDivide_BalancedQuadTree_Header
#define _SubDivide_BalancedQuadTree_Header

#include <SubDivide_QuadTreeNode.hxx>
#include <TColEntity_HAry1dOfBox2d.hxx>
#include <TColEntity_HBasicQueueOfBox2d.hxx>
#include <TColSubDivide_HBasicQueueOfQuadTreeNode.hxx>
#include <TColSubDivide_HArray1OfQuadTreeNode.hxx>
#include <Standard_Stream.hxx>
#include <SubDivide_QuadTreeQuadrant.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		template<typename T>
		class SubDivide_BalancedQuadTree
		{

		private:

			const Global_Handle(T) theObject_;

			Global_Handle(SubDivide_QuadTreeNode) theRoot_;

			Entity_Box2d theDomain_;

			Standard_Integer theMax_Level_;
			Standard_Integer theMin_Level_;

			TColSubDivide_HBasicQueueOfQuadTreeNode theTerminals_;

			Standard_Boolean(*theSubdivider)(const Entity_Box2d&, const Global_Handle(T));

		public:

			SubDivide_BalancedQuadTree();

			~SubDivide_BalancedQuadTree();

			void SetDomain(const Entity_Box2d& Domain);

			void SetObject(const Global_Handle(T) Object);

			void SetSubDivider(Standard_Boolean(*Subdivider)(const Entity_Box2d&, const Global_Handle(T)));

			void SetMaxLevel(const Standard_Integer Value);

			void SetMinLevel(const Standard_Integer Value);

			void Init();

			void Perform();

			void ExportToPlt(fstream& File) const;

			void RetrieveTo(TColEntity_HAry1dOfBox2d& Boxes) const;

			void RetrieveTo(TColSubDivide_HArray1OfQuadTreeNode& Nodes) const;

		private:

			Standard_Integer FindQuadrant(Global_Handle(SubDivide_QuadTreeNode) Pointer) const;

			void ForceDivide(Global_Handle(SubDivide_QuadTreeNode) & Node);

			void Balance(Global_Handle(SubDivide_QuadTreeNode) & Node);

			void CreateQuadrant(Global_Handle(SubDivide_QuadTreeNode) & Node, const Standard_Integer Quadrant);

			void RetrieveTo(Global_Handle(SubDivide_QuadTreeNode) Pointer, TColSubDivide_HBasicQueueOfQuadTreeNode& Nodes) const;

			void RetrieveTo(Global_Handle(SubDivide_QuadTreeNode) Pointer, TColEntity_HBasicQueueOfBox2d& Boxes) const;

			void Clear(Global_Handle(SubDivide_QuadTreeNode) &Pointer);
		};
	}
}

#include <SubDivide_BalancedQuadTreeI.hxx>

#endif // !_SubDivide_BalancedQuadTree_Header
