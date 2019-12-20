#pragma once
#ifndef _IO_STEPRead_Header
#define _IO_STEPRead_Header

#include <Standard_String.hxx>
#include <Standard_Real.hxx>

class TopoDS_Shape;

namespace AutLib
{
	namespace IoLib
	{

		class IO_STEPRead
		{

		public:

			static void ReadFile(const Standard_String& FileName, TopoDS_Shape& Shape, const Standard_Real Deflection = 0.01, const Standard_Real Angle = 0.1);

			static void ReadFileNonDiscretized(const Standard_String& FileName, TopoDS_Shape& Shape);
		};
	}
}

#endif // !_IO_STEPRead_Header
