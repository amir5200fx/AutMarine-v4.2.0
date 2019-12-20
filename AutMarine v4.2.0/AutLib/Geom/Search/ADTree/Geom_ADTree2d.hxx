#pragma once
#ifndef _Geom_ADTree2d_Header
#define _Geom_ADTree2d_Header

#include <Geom_ADTree2dNode.hxx>
#include <Geom_Search2d.hxx>
#include <ADT_BasicQueue.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		template<typename T>
		class Geom_ADTree2d : public Geom_Search2d<T>
		{

		private:

			Geom_ADTree2dNode<T> * Root_;

			Entity_Box2d Region_;

			Standard_Integer NbItems_;

			const Geom_Pnt2d &(*Get_Coordinates_)(T Item);

		public:

			Geom_ADTree2d();

			Geom_ADTree2d(const Entity_Box2d & Region, const Geom_Pnt2d &(*Get_Coordinates)(const T &));

			~Geom_ADTree2d();

			Standard_Integer Size() const;

			Standard_Boolean IsEmpty() const;

			const Entity_Box2d& BoundingBox() const;

			void SetCoordinateFunction(const Geom_Pnt2d &(*Get_Coordinates)(T));

			void Insert(const T& Item);

			void Insert(const ADT_Ary1d<T>& Items);

			void Remove(const T& Item);

			void RetrieveTo(ADT_Ary1d<T>& Items) const;

			void SetRegion(const Entity_Box2d& Region);

			void Search(const Entity_Box2d& Region, ADT_Ary1d<T>& Items) const;

			void Clear();

		private:

			void RetrieveTo(ADT_BasicQueue<T>& Items, Geom_ADTree2dNode<T> * t) const;

			void Insert(const T & Item, const Entity_Box2d & Region, Standard_Integer Level, Geom_ADTree2dNode<T> * & t);

			void Remove(const T & Item, Geom_ADTree2dNode<T> * & t);

			void Search(const Entity_Box2d & Region, Geom_ADTree2dNode<T> * t, ADT_BasicQueue<T> & Items) const;

			void Clear(Geom_ADTree2dNode<T> * t);

			inline void FindLeaf(Geom_ADTree2dNode<T> * t, Geom_ADTree2dNode<T> *& Leaf)
			{
				if (t == NULL)
					Leaf = NULL;
				else if (t->Left_ == NULL && t->Right_ == NULL)
					Leaf = t;
				else if (t->Left_ != NULL)
					FindLeaf(t->Left_, Leaf);
				else
					FindLeaf(t->Right_, Leaf);
			}
		};
	}
}

#include <Geom_ADTree2dI.hxx>

#endif // !_Geom_ADTree2d_Header
