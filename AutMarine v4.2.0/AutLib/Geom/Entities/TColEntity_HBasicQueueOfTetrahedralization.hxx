#pragma once
#ifndef _TColEntity_HBasicQueueOfTetrahedralization_Header
#define _TColEntity_HBasicQueueOfTetrahedralization_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <ADT_BasicQueue.hxx>

M_GEO_SPACE(Entity_Tetrahedralization)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_GEO Entity_Tetrahedralization)> TColEntity_HBasicQueueOfTetrahedralization;
}

#endif // !_TColEntity_HBasicQueueOfTetrahedralization_Header
