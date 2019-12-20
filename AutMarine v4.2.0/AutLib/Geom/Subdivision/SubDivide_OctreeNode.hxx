#pragma once
#ifndef _SubDivide_OctreeNode_Header
#define _SubDivide_OctreeNode_Header

#include <Entity_Box3d.hxx>
#include <Global_Memory.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class SubDivide_OctreeNode
		{

		private:

			Standard_Integer theLevel_;

			Entity_Box3d theBox_;

			Global_Handle(SubDivide_OctreeNode) theBwd_SwPointer_;
			Global_Handle(SubDivide_OctreeNode) theBwd_SePointer_;
			Global_Handle(SubDivide_OctreeNode) theBwd_NePointer_;
			Global_Handle(SubDivide_OctreeNode) theBwd_NwPointer_;
			Global_Handle(SubDivide_OctreeNode) theFwd_SwPointer_;
			Global_Handle(SubDivide_OctreeNode) theFwd_SePointer_;
			Global_Handle(SubDivide_OctreeNode) theFwd_NePointer_;
			Global_Handle(SubDivide_OctreeNode) theFwd_NwPointer_;

		public:

			SubDivide_OctreeNode();

			SubDivide_OctreeNode(const Standard_Integer Level, const Entity_Box3d& Box);

			Global_Handle(SubDivide_OctreeNode) Bwd_SwPointer() const;

			Global_Handle(SubDivide_OctreeNode) Bwd_SePointer() const;

			Global_Handle(SubDivide_OctreeNode) Bwd_NePointer() const;

			Global_Handle(SubDivide_OctreeNode) Bwd_NwPointer() const;

			Global_Handle(SubDivide_OctreeNode) Fwd_SwPointer() const;

			Global_Handle(SubDivide_OctreeNode) Fwd_SePointer() const;

			Global_Handle(SubDivide_OctreeNode) Fwd_NePointer() const;

			Global_Handle(SubDivide_OctreeNode) Fwd_NwPointer() const;

			Global_Handle(SubDivide_OctreeNode)& Bwd_SwPointer();

			Global_Handle(SubDivide_OctreeNode)& Bwd_SePointer();

			Global_Handle(SubDivide_OctreeNode)& Bwd_NePointer();

			Global_Handle(SubDivide_OctreeNode)& Bwd_NwPointer();

			Global_Handle(SubDivide_OctreeNode)& Fwd_SwPointer();

			Global_Handle(SubDivide_OctreeNode)& Fwd_SePointer();

			Global_Handle(SubDivide_OctreeNode)& Fwd_NePointer();

			Global_Handle(SubDivide_OctreeNode)& Fwd_NwPointer();

			Standard_Integer Level() const;

			const Entity_Box3d& Box() const;

			void SetBox(const Entity_Box3d& Box);

			void SetLevel(const Standard_Integer Value);

			void Init(Global_Handle(SubDivide_OctreeNode) theBwd_SwPointer, Global_Handle(SubDivide_OctreeNode) theBwd_SePointer, Global_Handle(SubDivide_OctreeNode) theBwd_NePointer, Global_Handle(SubDivide_OctreeNode) theBwd_NwPointer, Global_Handle(SubDivide_OctreeNode) theFwd_SwPointer, Global_Handle(SubDivide_OctreeNode) theFwd_SePointer, Global_Handle(SubDivide_OctreeNode) theFwd_NePointer, Global_Handle(SubDivide_OctreeNode) theFwd_NwPointer);

			void SetBwd_SwPointer(Global_Handle(SubDivide_OctreeNode) thePointer);

			void SetBwd_SePointer(Global_Handle(SubDivide_OctreeNode) thePointer);

			void SetBwd_NePointer(Global_Handle(SubDivide_OctreeNode) thePointer);

			void SetBwd_NwPointer(Global_Handle(SubDivide_OctreeNode) thePointer);

			void SetFwd_SwPointer(Global_Handle(SubDivide_OctreeNode) thePointer);

			void SetFwd_SePointer(Global_Handle(SubDivide_OctreeNode) thePointer);

			void SetFwd_NePointer(Global_Handle(SubDivide_OctreeNode) thePointer);

			void SetFwd_NwPointer(Global_Handle(SubDivide_OctreeNode) thePointer);
		};
	}
}

#include <SubDivide_OctreeNodeI.hxx>

#endif // !_SubDivide_OctreeNode_Header
