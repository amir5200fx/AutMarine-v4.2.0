#pragma once
#ifndef _Geom_ADTree3dNode_Header
#define _Geom_ADTree3dNode_Header

#include <Entity_Box3d.hxx>
#include <Standard_Integer.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		template<typename T>
		class Geom_ADTree3d;

		template<typename T>
		class Geom_ADTree3dNode
		{

			friend class Geom_ADTree3d<T>;

		private:

			Geom_ADTree3dNode<T> * Left_;
			Geom_ADTree3dNode<T> * Right_;

			Entity_Box3d Region_;

			T Data_;

			Standard_Integer Level_;

		public:

			Geom_ADTree3dNode(const T & Item, const Entity_Box3d & Region, const Standard_Integer Level, Geom_ADTree3dNode<T> * Left, Geom_ADTree3dNode<T> * Right);
		};
	}
}

#include <Geom_ADTree3dNodeI.hxx>

#endif // !_Geom_ADTree3dNode_Header
