#pragma once
#ifndef _Geom_BalancedPrOctTree_Header
#define _Geom_BalancedPrOctTree_Header

#include <Geom_PrOctantTreeLeaf.hxx>
#include <Geom_PrOctantTreeInternal.hxx>
#include <Geom_PrOctantInfo.hxx>
#include <TColEntity_HBasicQueueOfBox3d.hxx>
#include <TColEntity_HAry1dOfBox3d.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		template<typename T>
		class Geom_BalancedPrOctTree
		{

		private:

			Geom_PrOctantTreeNode<T>* theRoot_;

			Entity_Box3d theDomain_;

			Standard_Integer theNbItems_;
			Standard_Integer theInnerSubdivision_;

			Standard_Integer theBUCKET_SIZE_;
			Standard_Integer theMAX_INNER_SUBDIVISION_;

			Standard_Boolean IsBalancing_;

			const Geom_Pnt3d &(*theCoordOf)(T);

		public:

			Geom_BalancedPrOctTree();

			~Geom_BalancedPrOctTree();

			Standard_Integer Size() const;

			Standard_Boolean IsEmpty() const;

			const Entity_Box3d& BoundingBox() const;

			void SetCoordinateFunction(const Geom_Pnt3d &(*Get_Coordinates)(T));

			void SetMaxInnerSubdivision(const Standard_Integer Value);

			void SetBucketSize(const Standard_Integer Value);

			// Throw exception
			void Insert(const T& Item);

			// Throw exception
			void Insert(const ADT_Ary1d<T>& Items);

			void PostBalancing();

			void RetrieveTo(ADT_Ary1d<T>& Items) const;

			void RetrieveTo(TColEntity_HAry1dOfBox3d& Boxes) const;

			void SetRegion(const Entity_Box3d& Region);

			void Search(const Entity_Box3d& Region, ADT_Ary1d<T>& Items) const;

			void ExportToPlt(fstream& File) const;

		private:

			Geom_PrOctantInfo CalcOctant(const Geom_Pnt3d& P, const Geom_Pnt3d& Centre) const;

			Standard_Boolean DoSubdivide(Geom_PrOctantTreeLeaf<T>* Leaf) const;

			void Balancing(Geom_PrOctantTreeNode<T>* &t);

			void InnerLinks(Geom_PrOctantTreeInternal<T>* t);

			void RemoveLeafFromNeighbors(Geom_PrOctantTreeLeaf<T>* Old);

			void FillNeighbors(Geom_PrOctantInfo Quadrant, Geom_PrOctantTreeLeaf<T>* Old, Geom_PrOctantTreeInternal<T>* Father, Geom_PrOctantTreeLeaf<T> *t);

			void RetrieveTo(Geom_PrOctantTreeNode<T>* t, ADT_BasicQueue<T>& Items) const;

			void RetrieveTo(Geom_PrOctantTreeNode<T>* t, TColEntity_HBasicQueueOfBox3d& Boxes) const;

			void Insert(const T& Item, const Entity_Box3d& Region, Geom_PrOctantTreeNode<T>* & t);

			void Clear(Geom_PrOctantTreeNode<T>* & t);
		};
	}
}

#include <Geom_BalancedPrOctTreeI.hxx>

#endif // !_Geom_BalancedPrOctTree_Header
