#pragma once
#ifndef _Cad3d_WireOnPlaneOrientationTools_Header
#define _Cad3d_WireOnPlaneOrientationTools_Header

#include <Cad3d_WireOnPlaneOrientationInfo.hxx>
#include <TColCad3d_HAry1dOfEdgeOnPlane.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Cad3d_WireOnPlaneOrientationTools
		{

		public:

			static Cad3d_WireOnPlaneOrientationInfo ReverseOf(const Cad3d_WireOnPlaneOrientationInfo& theOrientation);

			static Cad3d_WireOnPlaneOrientationInfo RetrieveOrientationOf(const TColCad3d_HAry1dOfEdgeOnPlane& theEdges);
		};
	}
}

#include <Cad3d_WireOnPlaneOrientationToolsI.hxx>

#endif // !_Cad3d_WireOnPlaneOrientationTools_Header
