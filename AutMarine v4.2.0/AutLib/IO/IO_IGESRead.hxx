#pragma once
#ifndef _IO_IGESRead_Header
#define _IO_IGESRead_Header

#include <Standard_String.hxx>
#include <Standard_Real.hxx>

class TopoDS_Shape;

namespace AutLib
{
	namespace CadLib
	{
		class Cad3d_Solid;
	}

	namespace IoLib
	{

		class IO_IGESRead
		{

		public:

			static void ReadFile(const Standard_String& FileName, TopoDS_Shape& Shape, const Standard_Real Deflection = 0.01, const Standard_Real Angle = 0.1);

			static void ReadFileNonDiscretized(const Standard_String& FileName, TopoDS_Shape& Shape);

			static void ReadFile(const Standard_String& FileName, CadLib::Cad3d_Solid& theSolid, const Standard_Real Deflection = 0.01, const Standard_Real Angle = 0.1, const Standard_Real Tolerance = 1.0E-6, const Standard_Real Discrete = Standard_True);
		};
	}
}

#endif // !_IO_IGESRead_Header
