#pragma once
#ifndef _Mesh3d_SourcePointTools_Header
#define _Mesh3d_SourcePointTools_Header

#include <Mesh3d_SourcePoint.hxx>
#include <Global_Memory.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_SourcePointTools
		{

		public:

			static const Geom_Pnt3d& CoordinateOf(Global_Handle(Mesh3d_SourcePoint) theSource);
		};
	}
}

#include <Mesh3d_SourcePointToolsI.hxx>

#endif // !_Mesh3d_SourcePointTools_Header
