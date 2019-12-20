#pragma once
#ifndef _Cad2d_BooleanOperators_Header
#define _Cad2d_BooleanOperators_Header

#include <Global_Memory.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Cad2d_Plane;

		class Cad2d_BooleanOperators
		{

		public:

			static void Union(const Global_Handle(Cad2d_Plane) thePlane1, const Global_Handle(Cad2d_Plane) thePlane2, Global_Handle(Cad2d_Plane) theSum);

			static void Subtract(const Global_Handle(Cad2d_Plane) theTarget, const Global_Handle(Cad2d_Plane) thePlane, Global_Handle(Cad2d_Plane) theSum);

			static void Intersect(const Global_Handle(Cad2d_Plane) thePlane1, const Global_Handle(Cad2d_Plane) thePlane2, Global_Handle(Cad2d_Plane) theSum);
		};
	}
}

#endif // !_Cad2d_BooleanOperators_Header
