#pragma once
#ifndef _TColGeom_BasicQueueOfPnt2d_Header
#define _TColGeom_BasicQueueOfPnt2d_Header

#include <ADT_BasicQueue.hxx>
#include <Geom_Pnt2d.hxx>

namespace AutLib
{
	typedef ADT_BasicQueue<Geom_Pnt2d> TColGeom_BasicQueueOfPnt2d;
}

#endif // !_TColGeom_BasicQueueOfPnt2d_Header