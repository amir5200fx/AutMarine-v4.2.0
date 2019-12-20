#pragma once
#ifndef _Cad2d_PlaneTools_Header
#define _Cad2d_PlaneTools_Header

#include <Global_Memory.hxx>
#include <Standard_TypeDef.hxx>

class TopoDS_Face;

namespace AutLib
{
	namespace CadLib
	{

		class Cad2d_Plane;

		class Cad2d_PlaneTools
		{

		public:

			//! Warning: the plane is not removed from memory automatically!
			static Global_Handle(Cad2d_Plane) GetPlane(const TopoDS_Face& theSurface, const Standard_Real theTolerance = 1.0E-6, const Standard_Boolean theVerbose = Standard_False);
		};
	}
}

#endif // !_Cad2d_PlaneTools_Header
