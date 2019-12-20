#pragma once
#ifndef _TColGeom_BasicQueueOfPnt3d_Header
#define _TColGeom_BasicQueueOfPnt3d_Header

#include <ADT_BasicQueue.hxx>
#include <Geom_Pnt3d.hxx>

namespace AutLib
{
	typedef ADT_BasicQueue<Geom_Pnt3d> TColGeom_BasicQueueOfPnt3d;
}

#endif // !_TColGeom_BasicQueueOfPnt2d_Header