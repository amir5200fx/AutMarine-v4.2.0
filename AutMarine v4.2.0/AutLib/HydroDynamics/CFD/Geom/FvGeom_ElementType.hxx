#pragma once
#ifndef _FvGeom_ElementType_Header
#define _FvGeom_ElementType_Header

namespace AutLib
{
	namespace FvLib
	{

		enum FvGeom_ElementType
		{
			FvGeom_ElementType_Line = 0,
			FvGeom_ElementType_Triangle,
			FvGeom_ElementType_Quadrangle,
			FvGeom_ElementType_Tetrahedron,
			FvGeom_ElementType_Hexahedron,
			FvGeom_ElementType_Prism,
			FvGeom_ElementType_Pyramid,
			FvGeom_ElementType_Second_Line,
			FvGeom_ElementType_Second_Triangle,
			FvGeom_ElementType_Second_Tetrahedron,
			FvGeom_ElementType_Point,
			FvGeom_ElementType_Polygon,
			FvGeom_ElementType_Polyhedral
		};
	}
}

#endif // !_FvGeom_ElementType_Header