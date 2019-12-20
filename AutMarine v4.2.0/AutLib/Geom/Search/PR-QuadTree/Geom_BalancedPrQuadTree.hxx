#pragma once
#ifndef _Geom_BalancedPrQuadTree_Header
#define _Geom_BalancedPrQuadTree_Header

#include <Geom_PrQuadTreeLeaf.hxx>
#include <Geom_PrQuadTreeInternal.hxx>
#include <Geom_Pnt2d.hxx>
#include <Geom_PrQuadrant.hxx>
#include <Geom_Search2d.hxx>
#include <Standard_Stream.hxx>
#include <TColEntity_HAry1dOfBox2d.hxx>
#include <TColEntity_HBasicQueueOfBox2d.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		template<typename T>
		class Geom_BalancedPrQuadTree
		{

		private:

			Geom_PrQuadTreeNode<T>* theRoot_;

			Entity_Box2d theDomain_;

			Standard_Integer theNbItems_;
			Standard_Integer theInnerSubdivision_;

			const Geom_Pnt2d &(*theCoordOf)(T Item);

			Standard_Integer theBUCKET_SIZE_;
			Standard_Integer theMAX_INNER_SUBDIVISION_;

			Standard_Boolean IsBalancing_;

		public:

			Geom_BalancedPrQuadTree();

			~Geom_BalancedPrQuadTree();

			Standard_Integer Size() const;

			Standard_Boolean IsEmpty() const;

			const Entity_Box2d& BoundingBox() const;

			void SetCoordinateFunction(const Geom_Pnt2d &(*Get_Coordinates)(T));

			void SetMaxInnerSubdivision(const Standard_Integer Value);

			void SetBucketSize(const Standard_Integer Value);

			// Throw exception
			void Insert(const T& Item);

			// Throw exception
			void Insert(const ADT_Ary1d<T>& Items);

			// Throw exception
			void Remove(const T& Item);

			void PostBalancing();

			//void RetrieveTo(ADT_Ary1d<T>& Items) const;

			void RetrieveTo(TColEntity_HAry1dOfBox2d& Boxes) const;

			void SetRegion(const Entity_Box2d& Region);

			//void Search(const Entity_Box2d& Region, ADT_Ary1d<T>& Items) const;

			void ExportToPlt(fstream& File) const;

		private:

			Geom_PrQuadrant CalcQuadrant(const Geom_Pnt2d& P, const Geom_Pnt2d& Centre) const;

			void Balancing(Geom_PrQuadTreeNode<T>* &t);

			void RemoveLeafFromNeighbors(Geom_PrQuadTreeLeaf<T>* Old);

			void InnerLinks(Geom_PrQuadTreeInternal<T>* Father);

			void FillNeighbors(Geom_PrQuadrant Quadrant, Geom_PrQuadTreeLeaf<T>* Old, Geom_PrQuadTreeInternal<T>* Father, Geom_PrQuadTreeLeaf<T> *t);

			//void RetrieveTo(Geom_PrQuadTreeNode<T>* t, ADT_BasicQueue<T>& Items) const;

			void RetrieveTo(Geom_PrQuadTreeNode<T>* t, TColEntity_HBasicQueueOfBox2d& Boxes) const;

			void Insert(const T& Item, const Entity_Box2d& Region, /*ADT_Ary1d<Geom_PrQuadTreeLeaf<T>*>* SNeighbors, ADT_Ary1d<Geom_PrQuadTreeLeaf<T>*>* ENeighbors, ADT_Ary1d<Geom_PrQuadTreeLeaf<T>*>* NNeighbors, ADT_Ary1d<Geom_PrQuadTreeLeaf<T>*>* WNeighbors,*/ /*Geom_PrQuadTreeNode<T>* Father,*/ Geom_PrQuadTreeNode<T>* & t);

			void Remove(const T& Item, Geom_PrQuadTreeNode<T>* & t);

			void Search(const Entity_Box2d& Region, Geom_PrQuadTreeNode<T>* t, ADT_BasicQueue<T>& Items) const;

			void Clear(Geom_PrQuadTreeNode<T>* & t);
		};
	}
}

#include <Geom_BalancedPrQuadTreeI.hxx>

#endif // !_Geom_BalancedPrQuadTree_Header
