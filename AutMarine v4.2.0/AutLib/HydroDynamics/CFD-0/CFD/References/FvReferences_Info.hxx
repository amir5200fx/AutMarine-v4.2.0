#pragma once
#ifndef _FvReferences_Info_Header
#define _FvReferences_Info_Header

#include <Geom_Pnt2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvReferences_Info
		{

		public:

			static Geom_Pnt2d Gravity();

			static Standard_Real Pressure();
		};
	}
}

#endif // !_FvReferences_Info_Header
