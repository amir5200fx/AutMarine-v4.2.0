#pragma once
#ifndef _Cad2d_SketchMaxCoords_Header
#define _Cad2d_SketchMaxCoords_Header

#include <Standard_TypeDef.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Cad2d_SketchMaxCoords
		{

		public:

			static Standard_Real MaxXCoord();

			static Standard_Real MaxYCoord();

			static Standard_Real MinXCoord();

			static Standard_Real MinYCoord();
		};
	}
}

#endif // !_Cad2d_SketchMaxCoords_Header
