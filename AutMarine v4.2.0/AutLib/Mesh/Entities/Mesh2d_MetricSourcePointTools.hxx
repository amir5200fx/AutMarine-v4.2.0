#pragma once
#ifndef _Mesh2d_MetricSourcePointTools_Header
#define _Mesh2d_MetricSourcePointTools_Header

#include <Global_Memory.hxx>
#include <Mesh2d_MetricSourcePoint.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh2d_MetricSourcePointTools
		{

		public:

			static const Geom_Pnt2d& CoordinateOf(Global_Handle(Mesh2d_MetricSourcePoint) theSource);
		};
	}
}

#include <Mesh2d_MetricSourcePointToolsI.hxx>

#endif // !_Mesh2d_MetricSourcePointTools_Header
