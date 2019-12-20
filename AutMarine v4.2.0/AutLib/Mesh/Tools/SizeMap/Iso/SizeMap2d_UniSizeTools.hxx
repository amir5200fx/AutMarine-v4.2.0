#pragma once
#ifndef _SizeMap2d_UniSizeTools_Header
#define _SizeMap2d_UniSizeTools_Header

#include <Global_Memory.hxx>

namespace AutLib
{
	namespace GeoLib
	{
		class GeoMesh_BackGroundMesh2d;
		class Entity_Box2d;
	}

	namespace MeshLib
	{

		class SizeMap2d_UniSize;

		class SizeMap2d_UniSizeTools
		{

		public:

			static Global_Handle(GeoLib::GeoMesh_BackGroundMesh2d) GetBackMeshFrom(const SizeMap2d_UniSize& theSizeMap, const GeoLib::Entity_Box2d& theBox);
		};
	}
}

#endif // !_SizeMap2d_Tools_Header
