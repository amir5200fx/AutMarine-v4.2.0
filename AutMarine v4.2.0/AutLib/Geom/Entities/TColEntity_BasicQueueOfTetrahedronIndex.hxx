#pragma once
#ifndef _TColEntity_BasicQueueOfTetrahedronIndex_Header
#define _TColEntity_BasicQueueOfTetrahedronIndex_Header

#include <Global_Macros.hxx>
#include <ADT_BasicQueue.hxx>
#include <Entity_TetrahedronIndex.hxx>

namespace AutLib
{
	typedef ADT_BasicQueue<M_GEO Entity_TetrahedronIndex> TColEntity_BasicQueueOfTetrahedronIndex;
}

#endif // !_TColEntity_BasicQueueOfTetrahedronIndex_Header
