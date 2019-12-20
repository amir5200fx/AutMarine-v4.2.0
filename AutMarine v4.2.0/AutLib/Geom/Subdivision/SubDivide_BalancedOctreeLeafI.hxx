#pragma once
inline 
AutLib::GeoLib::SubDivide_BalancedOctreeLeaf::SubDivide_BalancedOctreeLeaf
(
	const Standard_Integer theLevel,
	const Entity_Box3d& theBox
)
	: SubDivide_BalancedOctreeNode(theLevel)
	, theBox_(theBox)
	, theFather_(0)
{
}

inline 
AutLib::GeoLib::SubDivide_BalancedOctreeLeaf::~SubDivide_BalancedOctreeLeaf()
{
}