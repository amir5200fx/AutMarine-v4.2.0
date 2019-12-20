#pragma once
#ifndef _TGeoMesh_TriangleMesh2dBoundaryList_Header
#define _TGeoMesh_TriangleMesh2dBoundaryList_Header

#include <TColEntity_HAry1dOfEdge2d.hxx>
#include <ADT_Ary1d.hxx>

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(TColEntity_HAry1dOfEdge2d)> TGeoMesh_TriangleMesh2dBoundaryList;
}

#endif // !_TGeoMesh_TriangleMesh2dBoundaryList_Header
