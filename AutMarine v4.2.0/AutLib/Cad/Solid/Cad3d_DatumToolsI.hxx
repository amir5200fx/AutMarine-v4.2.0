#pragma once
#include <Global_Debug.hxx>
inline
const Geom_Pnt3d & AutLib::CadLib::Cad3d_DatumTools::GetCoordOf(Global_Handle(Cad3d_Datum) theDatum)
{
	Debug_Null_Pointer(theDatum);
	return theDatum->Coord();
}