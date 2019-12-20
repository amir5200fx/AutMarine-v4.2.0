#pragma once
#ifndef _TColCad3d_HBasicQueueOfDatum_Header
#define _TColCad3d_HBasicQueueOfDatum_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <ADT_BasicQueue.hxx>

M_CAD_SPACE(Cad3d_Datum)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_CAD Cad3d_Datum)> TColCad3d_HBasicQueueOfDatum;
}

#endif // !_TColCad3d_HBasicQueueOfDatum_Header
