#pragma once
#ifndef _Cad3d_BooleanOperators_Header
#define _Cad3d_BooleanOperators_Header

#include <Global_Memory.hxx>
#include <Standard_TypeDef.hxx>

class TopoDS_Shape;

namespace AutLib
{
	namespace CadLib
	{
		class Cad3d_Solid;

		class Cad3d_BooleanOperators
		{

		public:

			static TopoDS_Shape Union(const TopoDS_Shape & theSolid1, const TopoDS_Shape & theSolid2);

			static TopoDS_Shape Subtract(const TopoDS_Shape & theTarget, const TopoDS_Shape & theSolid);

			static TopoDS_Shape Intersect(const TopoDS_Shape & theSolid1, const TopoDS_Shape & theSolid2);
		};
	}
}

#endif // !_Cad3d_BooleanOperators_Header
