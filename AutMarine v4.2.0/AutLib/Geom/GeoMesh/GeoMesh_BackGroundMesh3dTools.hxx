#pragma once
#ifndef _GeoMesh_BackGroundMesh3dTools_Header
#define _GeoMesh_BackGroundMesh3dTools_Header

#include <TColMesh3d_HAry1dOfSourcePoint.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class GeoMesh_BackGroundMesh3d;

		class GeoMesh_BackGroundMesh3dTools
		{

		public:

			static void SetSourcesToMesh(const TColMesh3d_HAry1dOfSourcePoint& theSources, const Standard_Real theBaseSize, GeoMesh_BackGroundMesh3d& theMesh);
		};
	}
}

#endif // !_GeoMesh_BackGroundMesh3dTools_header
