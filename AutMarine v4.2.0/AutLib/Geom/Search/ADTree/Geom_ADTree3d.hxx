#pragma once
#ifndef _Geom_ADTree3d_Header
#define _Geom_ADTree3d_Header

#include <Geom_ADTree3dNode.hxx>
#include <Geom_Search3d.hxx>
#include <ADT_BasicQueue.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		template<typename T>
		class Geom_ADTree3d : public Geom_Search3d<T>
		{

		private:

			Geom_ADTree3dNode<T> * Root_;

			Entity_Box3d Region_;

			Standard_Integer NbItems_;

			const Geom_Pnt3d &(*Get_Coordinates_)(T Item);

		public:

			Geom_ADTree3d();

			Geom_ADTree3d(const Entity_Box3d & Region, const Geom_Pnt3d &(*Get_Coordinates)(const T &));

			~Geom_ADTree3d();

			Standard_Integer Size() const;

			Standard_Boolean IsEmpty() const;

			const Entity_Box3d& BoundingBox() const;

			void SetCoordinateFunction(const Geom_Pnt3d &(*Get_Coordinates)(T));

			void Insert(const T& Item);

			void Insert(const ADT_Ary1d<T>& Items);

			void Remove(const T& Item);

			void Remove(const ADT_Ary1d<T>& Items);

			void RetrieveTo(ADT_Ary1d<T>& Items) const;

			void SetRegion(const Entity_Box3d& Region);

			void Search(const Entity_Box3d& Region, ADT_Ary1d<T>& Items) const;

			void Clear();

		private:

			void RetrieveTo(ADT_BasicQueue<T>& Items, Geom_ADTree3dNode<T> * t) const;

			void Insert(const T & Item, const Entity_Box3d & Region, Standard_Integer Level, Geom_ADTree3dNode<T> * & t);

			void Remove(const T & Item, Geom_ADTree3dNode<T> * & t);

			void Search(const Entity_Box3d & Region, Geom_ADTree3dNode<T> * t, ADT_BasicQueue<T> & Items) const;

			void FindLeaf(Geom_ADTree3dNode<T> * t, Geom_ADTree3dNode<T> *& Leaf) const;

			void Clear(Geom_ADTree3dNode<T> * t);
		};
	}
}

#include <Geom_ADTree3dI.hxx>

#endif // !_Geom_ADTree3d_Header
