#pragma once
#ifndef _SubDivide_QuadTree_Header
#define _SubDivide_QuadTree_Header

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
		class SubDivide_QuadTree
		{

		private:

			const Global_Handle(T) theObject_;

			Global_Handle(SubDivide_QuadTreeNode) theRoot_;

			Entity_Box2d theDomain_;

			Standard_Integer theMax_Level_;
			Standard_Integer theMin_Level_;

			Standard_Boolean(*theSubdivider)(const Entity_Box2d&, const Global_Handle(T));

		public:

			SubDivide_QuadTree();

			SubDivide_QuadTree(const Entity_Box2d& Domain, const Global_Handle(T) Object, Standard_Boolean(*Subdivider)(const Entity_Box2d&, const Global_Handle(T)));

			SubDivide_QuadTree(const SubDivide_QuadTree& Other) = delete;

			~SubDivide_QuadTree();

			SubDivide_QuadTree& operator=(const SubDivide_QuadTree& Other) = delete;

			void SetDomain(const Entity_Box2d& Domain);

			void SetObject(const Global_Handle(T) Object);

			void SetSubDivider(Standard_Boolean(*Subdivider)(const Entity_Box2d&, const Global_Handle(T)));

			void SetMaxLevel(const Standard_Integer Value);

			void SetMinLevel(const Standard_Integer Value);

			void Init();

			void Perform(const TColSubDivide_HArray1OfQuadTreeNode& Nodes);

			void Perform();

			void RetrieveTo(TColEntity_HAry1dOfBox2d& Boxes) const;

			void RetrieveTo(TColSubDivide_HArray1OfQuadTreeNode& Nodes) const;

			void Search(const Entity_Box2d& Box, TColSubDivide_HArray1OfQuadTreeNode& Nodes) const;

			void ExportToPlt(fstream& File) const;

		private:

			Global_Handle(SubDivide_QuadTreeNode) CreateNode(const Standard_Integer Level, const Entity_Box2d& Box) const;

			Standard_Integer Quadrant(Global_Handle(SubDivide_QuadTreeNode) Pointer) const;

			void Balance(Global_Handle(SubDivide_QuadTreeNode) & Node);

			void SubDivide(Global_Handle(SubDivide_QuadTreeNode) & Node);

			void ForceDivide(Global_Handle(SubDivide_QuadTreeNode) & Node);

			void Search(const Entity_Box2d& Box, Global_Handle(SubDivide_QuadTreeNode) Pointer, TColSubDivide_HBasicQueueOfQuadTreeNode& Nodes) const;

			void RetrieveTo(Global_Handle(SubDivide_QuadTreeNode) Pointer, TColSubDivide_HBasicQueueOfQuadTreeNode& Nodes) const;

			void Clear(Global_Handle(SubDivide_QuadTreeNode) &Pointer);
		};
	}
}

#include <SubDivide_QuadTreeI.hxx>

#endif // !_SubDivide_QuadTree_Header
