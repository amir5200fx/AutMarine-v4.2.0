#pragma once
#ifndef _Cad2d_WireOnPlaneOrientationTools_Header
#define _Cad2d_WireOnPlaneOrientationTools_Header

#include <Cad2d_WireOnPlaneOrientationInfo.hxx>
#include <TColCad2d_HAry1dOfEdgeOnPlane.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Cad2d_WireOnPlaneOrientationTools
		{

		public:

			static Cad2d_WireOnPlaneOrientationInfo ReverseOf(const Cad2d_WireOnPlaneOrientationInfo& theOrientation);

			static Cad2d_WireOnPlaneOrientationInfo RetrieveOrientationOf(const TColCad2d_HAry1dOfEdgeOnPlane& theEdges);
		};
	}
}

#include <Cad2d_WireOnPlaneOrientationToolsI.hxx>

#endif // !_Cad2d_WireOnPlaneOrientationTools_Header
