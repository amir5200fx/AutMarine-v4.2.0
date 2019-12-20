#pragma once
#ifndef _SubDivide_Octree_Header
#define _SubDivide_Octree_Header

#include <SubDivide_OctreeNode.hxx>
#include <TColEntity_HAry1dOfBox3d.hxx>
#include <TColEntity_HBasicQueueOfBox3d.hxx>
#include <TColSubDivide_HBasicQueueOfOctreeNode.hxx>
#include <TColSubDivide_HAray1OfOctreeNode.hxx>
#include <Standard_Stream.hxx>
#include <SubDivide_OctreeOctant.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		template<typename T>
		class SubDivide_Octree
		{

		private:

			const Global_Handle(T) theObject_;

			Global_Handle(SubDivide_OctreeNode) theRoot_;

			Entity_Box3d theDomain_;

			Standard_Integer theMax_Level_;
			Standard_Integer theMin_Level_;

			Standard_Boolean(*theSubdivider)(const Entity_Box3d&, const Global_Handle(T));

		public:

			SubDivide_Octree();

			SubDivide_Octree(const Entity_Box3d& Domain, const Global_Handle(T) Object, Standard_Boolean(*Subdivider)(const Entity_Box3d&, const Global_Handle(T)));

			SubDivide_Octree(const SubDivide_Octree& Other) = delete;

			~SubDivide_Octree();

			SubDivide_Octree& operator=(const SubDivide_Octree& Other) = delete;

			void SetDomain(const Entity_Box3d& Domain);

			void SetObject(const Global_Handle(T) Object);

			void SetSubDivider(Standard_Boolean(*Subdivider)(const Entity_Box3d&, const Global_Handle(T)));

			void SetMaxLevel(const Standard_Integer Value);

			void SetMinLevel(const Standard_Integer Value);

			void Init();

			void Perform(const TColSubDivide_HAray1OfOctreeNode& Nodes);

			void Perform();

			void RetrieveTo(TColEntity_HAry1dOfBox3d& Boxes) const;

			void RetrieveTo(TColSubDivide_HAray1OfOctreeNode& Nodes) const;

			void Search(const Entity_Box3d& Box, TColSubDivide_HAray1OfOctreeNode& Nodes) const;

			void ExportToPlt(fstream& File) const;

		private:

			Global_Handle(SubDivide_OctreeNode) CreateNode(const Standard_Integer Level, const Entity_Box3d& Box) const;

			void SubDivide(Global_Handle(SubDivide_OctreeNode) & Node);

			void ForceDivide(Global_Handle(SubDivide_OctreeNode) & Node);

			void Search(const Entity_Box3d& Box, Global_Handle(SubDivide_OctreeNode) Pointer, TColSubDivide_HBasicQueueOfOctreeNode& Nodes) const;

			void RetrieveTo(Global_Handle(SubDivide_OctreeNode) Pointer, TColSubDivide_HBasicQueueOfOctreeNode& Nodes) const;

			void RetrieveTo(Global_Handle(SubDivide_OctreeNode) Pointer, TColEntity_HBasicQueueOfBox3d& Boxes) const;

			void Clear(Global_Handle(SubDivide_OctreeNode) &Pointer);
		};
	}
}

#include <SubDivide_OctreeI.hxx>

#endif // !_Subdivide_Octree_Header
