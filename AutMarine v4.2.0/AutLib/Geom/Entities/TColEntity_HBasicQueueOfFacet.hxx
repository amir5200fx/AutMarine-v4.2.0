#pragma once
#ifndef _TColEntity_HBasicQueueOfFacet_Header
#define _TColEntity_HBasicQueueOfFacet_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Memory.hxx>

M_GEO_SPACE(Entity_Facet)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_GEO Entity_Facet)> TColEntity_HBasicQueueOfFacet;
}

#endif // !_TColEntity_HBasicQueueOfFacet_Header
