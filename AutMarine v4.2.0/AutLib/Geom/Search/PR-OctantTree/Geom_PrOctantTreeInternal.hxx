#pragma once
#ifndef _Geom_PrOctantTreeInternal_Header
#define _Geom_PrOctantTreeInternal_Header

#include <Geom_PrOctantTreeNode.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		template<typename T>
		class Geom_PrOctantTreeInternal : public Geom_PrOctantTreeNode<T>
		{

		public:

			Geom_PrOctantTreeNode<T>* theFwd_SwPtr_;
			Geom_PrOctantTreeNode<T>* theFwd_SePtr_;
			Geom_PrOctantTreeNode<T>* theFwd_NePtr_;
			Geom_PrOctantTreeNode<T>* theFwd_NwPtr_;
			Geom_PrOctantTreeNode<T>* theBwd_SwPtr_;
			Geom_PrOctantTreeNode<T>* theBwd_SePtr_;
			Geom_PrOctantTreeNode<T>* theBwd_NePtr_;
			Geom_PrOctantTreeNode<T>* theBwd_NwPtr_;

			Geom_PrOctantTreeInternal()
				: theFwd_SwPtr_(0)
				, theFwd_SePtr_(0)
				, theFwd_NePtr_(0)
				, theFwd_NwPtr_(0)
				, theBwd_SwPtr_(0)
				, theBwd_SePtr_(0)
				, theBwd_NePtr_(0)
				, theBwd_NwPtr_(0)
			{}

			virtual ~Geom_PrOctantTreeInternal()
			{
				FreePointer(theFwd_SwPtr_);
				FreePointer(theFwd_SePtr_);
				FreePointer(theFwd_NePtr_);
				FreePointer(theFwd_NwPtr_);
				FreePointer(theBwd_SwPtr_);
				FreePointer(theBwd_SePtr_);
				FreePointer(theBwd_NePtr_);
				FreePointer(theBwd_NwPtr_);
			}

		};
	}
}

#endif // !_Geom_PrOctantTreeInternal_Header
