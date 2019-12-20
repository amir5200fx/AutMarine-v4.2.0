#pragma once
#ifndef _GeoMesh_BackGroundMesh2dTools_Header
#define _GeoMesh_BackGroundMesh2dTools_Header

#include <Standard_Stream.hxx>
#include <Global_Memory.hxx>
#include <TColMesh2d_HAry1dOfSourcePoint.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class GeoMesh_BackGroundMesh2d;
		class GeoMesh_TriangleMesh2d;

		class GeoMesh_BackGroundMesh2dTools
		{

		public:

			//! Warning: the background mesh is not removed from memory automatically
			static Global_Handle(GeoMesh_BackGroundMesh2d) ReadBackMeshFrom(fstream& File, GeoMesh_TriangleMesh2d& theTriangleMesh);

			//! Warning: the background mesh is not removed from memory automatically
			static Global_Handle(GeoMesh_BackGroundMesh2d) ReadBackMeshFrom(fstream& File);

			static void SetSourcesToMesh(const TColMesh2d_HAry1dOfSourcePoint& theSources, const Standard_Real theBaseSize, GeoMesh_BackGroundMesh2d& theMesh);
		};
	}
}

#endif // !_GeoMesh_BackGroundMesh2dTools_Header
