#pragma once
#ifndef _Mesh2d_SourcePointTools_Header
#define _Mesh2d_SourcePointTools_Header

#include <Mesh2d_SourcePoint.hxx>
#include <Global_Memory.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh2d_SourcePointTools
		{

		public:

			static const Geom_Pnt2d& CoordinateOf(Global_Handle(Mesh2d_SourcePoint) theSource);
		};
	}
}

#include <Mesh2d_SourcePointToolsI.hxx>

#endif // !_Mesh2d_SourcePointTools_Header
