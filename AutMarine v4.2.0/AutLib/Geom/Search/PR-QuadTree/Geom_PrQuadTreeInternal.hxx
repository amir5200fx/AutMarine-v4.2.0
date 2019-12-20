#pragma once
#ifndef _Geom_PrQuadTreeInternal_Header
#define _Geom_PrQuadTreeInternal_Header

#include <Geom_PrQuadTreeNode.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		template<typename T>
		class Geom_PrQuadTreeInternal : public Geom_PrQuadTreeNode<T>
		{

		public:

			Geom_PrQuadTreeNode<T>* theSwPtr_;
			Geom_PrQuadTreeNode<T>* theSePtr_;
			Geom_PrQuadTreeNode<T>* theNePtr_;
			Geom_PrQuadTreeNode<T>* theNwPtr_;

			//Geom_Box2d theBox_;

			Geom_PrQuadTreeInternal()
				: theSwPtr_(0)
				, theSePtr_(0)
				, theNePtr_(0)
				, theNwPtr_(0)
			{}

			virtual ~Geom_PrQuadTreeInternal()
			{
				FreePointer(theSwPtr_);
				FreePointer(theSePtr_);
				FreePointer(theNePtr_);
				FreePointer(theNwPtr_);
			}

			inline Standard_Boolean IsEmpty() const
			{
				return (IsNULL(theSwPtr_) AND IsNULL(theSePtr_) AND IsNULL(theNwPtr_) AND IsNULL(theNePtr_));
			}
		};
	}
}

#endif // !_Geom_PrQuadTreeInternal_Header
