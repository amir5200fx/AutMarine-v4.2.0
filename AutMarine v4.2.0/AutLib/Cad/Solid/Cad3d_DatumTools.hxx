#pragma once
#ifndef _Cad3d_DatumTools_Header
#define _Cad3d_DatumTools_Header

#include <Global_Memory.hxx>
#include <Cad3d_Datum.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Cad3d_DatumTools
		{

		public:

			static const Geom_Pnt3d& GetCoordOf(Global_Handle(Cad3d_Datum) theDatum);
		};
	}
}

#include <Cad3d_DatumToolsI.hxx>

#endif // !_Cad3d_DatumTools_Header
