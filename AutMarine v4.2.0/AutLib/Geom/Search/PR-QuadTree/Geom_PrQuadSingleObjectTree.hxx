#pragma once
#ifndef _Geom_PrQuadSingleObjectTree_Header
#define _Geom_PrQuadSingleObjectTree_Header

#include <Geom_PrQuadTreeSingleObjectLeaf.hxx>
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
		class Geom_PrQuadSingleObjectTree : public Geom_Search2d<T>
		{

		private:

			Geom_PrQuadTreeNode<T>* theRoot_;

			Entity_Box2d theDomain_;

			Standard_Integer theNbItems_;
			Standard_Integer theInnerSubdivision_;

			const Geom_Pnt2d &(*theCoordOf)(T Item);

			Standard_Integer theMAX_INNER_SUBDIVISION_;

		public:

			Geom_PrQuadSingleObjectTree();

			~Geom_PrQuadSingleObjectTree();

			Standard_Integer Size() const;

			Standard_Boolean IsEmpty() const;

			const Entity_Box2d& BoundingBox() const;

			void SetCoordinateFunction(const Geom_Pnt2d &(*Get_Coordinates)(T));

			void SetMaxInnerSubdivision(const Standard_Integer Value);

			// Throw exception
			void Insert(const T& Item);

			// Throw exception
			void Insert(const ADT_Ary1d<T>& Items);

			// Throw exception
			void Remove(const T& Item);

			void RetrieveTo(ADT_Ary1d<T>& Items) const;

			void RetrieveTo(TColGeom_HArray1OfBox2d& Boxes) const;

			void SetRegion(const Entity_Box2d& Region);

			void Search(const Entity_Box2d& Region, ADT_Ary1d<T>& Items) const;

			void ExportToPlt(fstream& File) const;

		private:

			//Standard_Integer FindQuadrant(Geom_PrQuadTreeNode<T>* t) const;

			Geom_PrQuadrant CalcQuadrant(const Geom_Pnt2d& P, const Geom_Pnt2d& Centre) const;

			//void Balance(Geom_PrQuadTreeNode<T>* &t);

			//void CreateQuadrant(Geom_PrQuadTreeNode<T>* &t, const Standard_Integer Quadrant);

			void RetrieveTo(Geom_PrQuadTreeNode<T>* t, ADT_BasicQueue<T>& Items) const;

			void RetrieveTo(Geom_PrQuadTreeNode<T>* t, TColEntity_HBasicQueueOfBox2d& Boxes) const;

			void Insert(const T& Item, const Entity_Box2d& Region, Geom_PrQuadTreeNode<T>* Father, Geom_PrQuadTreeNode<T>* & t);

			void Remove(const T& Item, Geom_PrQuadTreeNode<T>* & t);

			void Search(const Entity_Box2d& Region, Geom_PrQuadTreeNode<T>* t, ADT_BasicQueue<T>& Items) const;

			void Clear(Geom_PrQuadTreeNode<T>* & t);
		};
	}
}

#include <Geom_PrQuadSingleObjectTreeI.hxx>

#endif // !_Geom_PrQuadSingleObjectTree_Header
