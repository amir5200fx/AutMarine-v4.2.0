#pragma once
#ifndef _Cad3d_RingOnSurfaceTools_Header
#define _Cad3d_RingOnSurfaceTools_Header

#include <Standard_Type.hxx>
#include <Global_Memory.hxx>

namespace AutLib
{
	namespace CadLib
	{
		class Cad3d_RingOnSurface;

		class Cad3d_RingOnSurfaceTools
		{

		public:

			static Standard_Boolean AreCoincident(const Cad3d_RingOnSurface& Ring1, const Cad3d_RingOnSurface& Ring2, const Standard_Real Tolerance = 1.0E-6);
		};
	}
}

#endif // !_Cad3d_RingOnSurfaceTools_Header
