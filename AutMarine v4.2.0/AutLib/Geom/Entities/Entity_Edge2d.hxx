#pragma once
#ifndef _Entity_Edge2d_Header
#define _Entity_Edge2d_Header

#include <Entity_Node2d.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Entity_Edge2d
		{

		private:

			Global_Handle(Entity_Node2d) theNodes_[2];

			Standard_Integer theIndex_;

			Standard_Boolean IsOnBoundary_;

			Global_Handle(Entity_Element2d) theRight_;
			Global_Handle(Entity_Element2d) theLeft_;

		public:

			Entity_Edge2d();

			Entity_Edge2d(const Standard_Integer Index, Global_Handle(Entity_Node2d) Node0, Global_Handle(Entity_Node2d) Node1);

			Standard_Integer Index() const;

			Standard_Boolean IsOnBoundary() const;

			Global_Handle(Entity_Node2d) Node(const Standard_Integer Index) const;

			Global_Handle(Entity_Node2d)& Node(const Standard_Integer Index);

			Global_Handle(Entity_Element2d) RightElement() const;

			Global_Handle(Entity_Element2d) LeftElement() const;

			void SetIndex(const Standard_Integer Index);

			void SetNode(const Standard_Integer Index, Global_Handle(Entity_Node2d) Node);

			void SetLeftElement(Global_Handle(Entity_Element2d) Element);

			void SetRightElement(Global_Handle(Entity_Element2d) Element);

			void SetAsBoundary();

			void SetAsNonBoundary();
		};
	}
}

#include <Entity_Edge2dI.hxx>

#endif // !_Entity_Edge2d_Header
