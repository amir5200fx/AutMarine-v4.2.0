#pragma once
#include <Global_Memory.hxx>
inline 
AutLib::GeoLib::SubDivide_BalancedOctreeInternal::SubDivide_BalancedOctreeInternal(const Standard_Integer theLevel)
	: SubDivide_BalancedOctreeNode(theLevel)
	, theFwd_SwPtr_(0)
	, theFwd_SePtr_(0)
	, theFwd_NePtr_(0)
	, theFwd_NwPtr_(0)
	, theBwd_SwPtr_(0)
	, theBwd_SePtr_(0)
	, theBwd_NePtr_(0)
	, theBwd_NwPtr_(0)
{
}

inline 
AutLib::GeoLib::SubDivide_BalancedOctreeInternal::~SubDivide_BalancedOctreeInternal()
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