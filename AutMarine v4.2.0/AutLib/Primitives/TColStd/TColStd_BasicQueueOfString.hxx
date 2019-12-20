#pragma once
#ifndef _TColStd_BasicQueueOfString_Header
#define _TColStd_BasicQueueOfString_Header

#include <Standard_String.hxx>
#include <Standard_Handle.hxx>
#include <ADT_BasicQueue.hxx>

namespace AutLib
{
	typedef ADT_BasicQueue<Standard_String> TColStd_BasicQueueOfString;
}

#endif // !_TColStd_BasicQueueOfString_Header
