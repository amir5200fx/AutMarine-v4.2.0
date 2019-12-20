#pragma once
#ifndef _Geom_PrOctantInfo_Header
#define _Geom_PrOctantInfo_Header

namespace AutLib
{
	namespace GeoLib
	{

		enum Geom_PrOctantInfo
		{
			Geom_PrOctantInfo_Fwd_SW,
			Geom_PrOctantInfo_Fwd_SE,
			Geom_PrOctantInfo_Fwd_NW,
			Geom_PrOctantInfo_Fwd_NE,
			Geom_PrOctantInfo_Bwd_SW,
			Geom_PrOctantInfo_Bwd_SE,
			Geom_PrOctantInfo_Bwd_NW,
			Geom_PrOctantInfo_Bwd_NE
		};
	}
}

#endif // !_Geom_PrOctantInfo_Header
