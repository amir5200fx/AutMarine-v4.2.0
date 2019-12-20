#pragma once
#ifndef _SubDivide_OctreeOctant_Header
#define _SubDivide_OctreeOctant_Header

namespace AutLib
{
	namespace GeoLib
	{

		enum SubDivide_OctreeOctant
		{
			SubDivide_OctreeOctant_Bwd_SW,
			SubDivide_OctreeOctant_Bwd_SE,
			SubDivide_OctreeOctant_Bwd_NE,
			SubDivide_OctreeOctant_Bwd_NW,
			SubDivide_OctreeOctant_Fwd_SW,
			SubDivide_OctreeOctant_Fwd_SE,
			SubDivide_OctreeOctant_Fwd_NE,
			SubDivide_OctreeOctant_Fwd_NW
		};
	}
}

#endif // !_Subdivide_OctreeOctant_Header
