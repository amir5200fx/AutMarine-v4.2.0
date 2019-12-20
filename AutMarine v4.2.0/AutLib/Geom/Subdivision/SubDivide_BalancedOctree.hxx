#pragma once
#ifndef _SubDivide_BalancedOctree_Header
#define _SubDivide_BalancedOctree_Header

#include <Standard_Stream.hxx>
#include <Geom_Pnt3d.hxx>
#include <SubDivide_OctreeOctant.hxx>
#include <SubDivide_BalancedOctreeLeaf.hxx>
#include <SubDivide_BalancedOctreeInternal.hxx>
#include <TColEntity_HAry1dOfBox3d.hxx>
#include <TColEntity_HBasicQueueOfBox3d.hxx>
#include <TColSubDivide_HBasicQueueOfBalancedOctreeNode.hxx>
#include <TColSubDivide_HAray1OfBalancedOctreeNode.hxx>

namespace AutLib
{
	namespace GeoLib
	{
		
		template<typename T>
		class SubDivide_BalancedOctree
		{

		private:

			const Global_Handle(T) theObject_;

			Global_Handle(SubDivide_BalancedOctreeNode) theRoot_;

			Entity_Box3d theDomain_;

			Standard_Boolean IsBalancing_;

			Standard_Integer theMax_Level_;
			Standard_Integer theMin_Level_;
			Standard_Integer theMaxUnBalancing_;

			Standard_Boolean(*theSubdivider)(const Entity_Box3d&, const Global_Handle(T));

		public:

			SubDivide_BalancedOctree();

			SubDivide_BalancedOctree(const Entity_Box3d& Domain, const Global_Handle(T) Object, Standard_Boolean(*Subdivider)(const Entity_Box3d&, const Global_Handle(T)));

			SubDivide_BalancedOctree(const SubDivide_BalancedOctree& Other) = delete;

			~SubDivide_BalancedOctree();

			SubDivide_BalancedOctree& operator=(const SubDivide_BalancedOctree& Other) = delete;

			void SetDomain(const Entity_Box3d& Domain);

			void SetObject(const Global_Handle(T) Object);

			void SetSubDivider(Standard_Boolean(*Subdivider)(const Entity_Box3d&, const Global_Handle(T)));

			void SetMaxLevel(const Standard_Integer Value);

			void SetMinLevel(const Standard_Integer Value);

			void SetMaxUnBalancingLevel(const Standard_Integer Value);

			void Init();

			void Perform(const TColSubDivide_HAray1OfBalancedOctreeNode& Nodes);

			void Perform();

			void PostBalancing();

			void RetrieveTo(TColEntity_HAry1dOfBox3d& Boxes) const;

			void RetrieveTo(TColSubDivide_HAray1OfBalancedOctreeNode& Nodes) const;

			void ExportToPlt(fstream& File) const;

		private:

			Standard_Boolean DoSubdivide(SubDivide_BalancedOctreeLeaf* Leaf) const;

			SubDivide_OctreeOctant CalcOctant(const Geom_Pnt3d& P, const Geom_Pnt3d& Centre) const;

			SubDivide_BalancedOctreeLeaf* CreateLeaf(const Standard_Integer Level, const Entity_Box3d& Box) const;

			void SubDivide(SubDivide_BalancedOctreeNode* & Node);

			void ForceDivide(SubDivide_BalancedOctreeNode*& Node);

			void UpdateFather(SubDivide_BalancedOctreeLeaf* Node, SubDivide_BalancedOctreeNode* Internal);

			void InnerLinks(SubDivide_BalancedOctreeInternal* t);

			void RemoveLeafFromNeighbors(SubDivide_BalancedOctreeLeaf* t);

			void FillNeighbors(SubDivide_OctreeOctant Octant, SubDivide_BalancedOctreeLeaf* Old, SubDivide_BalancedOctreeInternal* Father, SubDivide_BalancedOctreeLeaf* t);

			void Balancing(SubDivide_BalancedOctreeNode* &t);

			void RetrieveTo(Global_Handle(SubDivide_BalancedOctreeNode) Pointer, TColSubDivide_HBasicQueueOfBalancedOctreeNode& Nodes) const;

			void RetrieveTo(SubDivide_BalancedOctreeNode* t, TColEntity_HBasicQueueOfBox3d& Boxes) const;

			void Clear(SubDivide_BalancedOctreeNode* &t);
		};
	}
}

#include <SubDivide_BalancedOctreeI.hxx>

#endif // !_SubDivide_BalancedOctree_Header
