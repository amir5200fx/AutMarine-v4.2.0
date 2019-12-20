#pragma once
#ifndef _Cad3d_SurfaceOrientationTools_Header
#define _Cad3d_SurfaceOrientationTools_Header

#include <Cad3d_SurfaceOrientationInfo.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Cad3d_SurfaceOrientationTools
		{

		public:

			static Cad3d_SurfaceOrientationInfo ReverseOf(const Cad3d_SurfaceOrientationInfo theOrientation);
		};
	}
}

#endif // !_Cad3d_SurfaceOrientationTools_Header
