#pragma once
#ifndef _Geom2d_ADTree2dNode_Header
#define _Geom2d_ADTree2dNode_Header

#include <Entity_Box2d.hxx>
#include <Standard_Integer.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		template<typename T>
		class Geom_ADTree2d;

		template<typename T>
		class Geom_ADTree2dNode
		{

			friend class Geom_ADTree2d<T>;

		private:

			Geom_ADTree2dNode<T> * Left_;
			Geom_ADTree2dNode<T> * Right_;

			Entity_Box2d Region_;

			T Data_;

			Standard_Integer Level_;

		public:

			Geom_ADTree2dNode(const T & Item, const Entity_Box2d & Region, const Standard_Integer Level, Geom_ADTree2dNode<T> * Left, Geom_ADTree2dNode<T> * Right);
		};
	}
}

#include <Geom_ADTree2dNodeI.hxx>

#endif // !_Geom2d_ADTreeNode_Header
