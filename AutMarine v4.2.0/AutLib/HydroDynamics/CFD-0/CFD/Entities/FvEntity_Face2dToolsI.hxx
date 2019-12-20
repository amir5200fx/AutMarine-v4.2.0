#pragma once
inline
const Geom_Pnt2d & AutLib::FvLib::FvEntity_Face2dTools::GetCoordOf(Global_Handle(FvEntity_Face2d) theFace)
{
	return theFace->Centre();
}