#pragma once
#ifndef _SubDivide_QuadTreeNode_Header
#define _SubDivide_QuadTreeNode_Header

#include <Entity_Box2d.hxx>
#include <Global_Memory.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class SubDivide_QuadTreeNode
		{

		private:

			Standard_Integer theLevel_;

			Entity_Box2d theBox_;

			Global_Handle(SubDivide_QuadTreeNode) theSwPointer_;
			Global_Handle(SubDivide_QuadTreeNode) theSePointer_;
			Global_Handle(SubDivide_QuadTreeNode) theNwPointer_;
			Global_Handle(SubDivide_QuadTreeNode) theNePointer_;

			Global_Handle(SubDivide_QuadTreeNode) theFather_;

		public:

			SubDivide_QuadTreeNode();

			SubDivide_QuadTreeNode(const Standard_Integer Level, const Entity_Box2d& Box);

			Global_Handle(SubDivide_QuadTreeNode) SwPointer() const;

			Global_Handle(SubDivide_QuadTreeNode) SePointer() const;

			Global_Handle(SubDivide_QuadTreeNode) NwPointer() const;

			Global_Handle(SubDivide_QuadTreeNode) NePointer() const;

			Global_Handle(SubDivide_QuadTreeNode) Father() const;

			Global_Handle(SubDivide_QuadTreeNode)& SwPointer();

			Global_Handle(SubDivide_QuadTreeNode)& SePointer();

			Global_Handle(SubDivide_QuadTreeNode)& NwPointer();

			Global_Handle(SubDivide_QuadTreeNode)& NePointer();

			Global_Handle(SubDivide_QuadTreeNode)& Father();

			Standard_Integer Level() const;

			const Entity_Box2d& Box() const;

			void SetBox(const Entity_Box2d& Box);

			void SetLevel(const Standard_Integer Value);

			void SetPointers(Global_Handle(SubDivide_QuadTreeNode) Sw, Global_Handle(SubDivide_QuadTreeNode) Se, Global_Handle(SubDivide_QuadTreeNode) Nw, Global_Handle(SubDivide_QuadTreeNode) Ne);

			void SetSwPointer(Global_Handle(SubDivide_QuadTreeNode) Pointer);

			void SetSePointer(Global_Handle(SubDivide_QuadTreeNode) Pointer);

			void SetNwPointer(Global_Handle(SubDivide_QuadTreeNode) Pointer);

			void SetNePointer(Global_Handle(SubDivide_QuadTreeNode) Pointer);

			void SetFather(Global_Handle(SubDivide_QuadTreeNode) Pointer);
		};
	}
}

#include <SubDivide_QuadTreeNodeI.hxx>

#endif // !_SubDivide_QuadTreeNode_Header
