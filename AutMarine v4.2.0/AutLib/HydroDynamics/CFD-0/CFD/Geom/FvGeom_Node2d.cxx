#include <FvGeom_Node2d.hxx>

AutLib::FvLib::FvGeom_Node2d::FvGeom_Node2d()
{
}

AutLib::FvLib::FvGeom_Node2d::FvGeom_Node2d
(
	const Standard_Integer theIndex, 
	const Geom_Pnt2d & theCoord
)
	: theIndex_(theIndex)
	, theCoord_(theCoord)
{
}

void AutLib::FvLib::FvGeom_Node2d::Import(fstream & File)
{
	File >> theIndex_ >> theCoord_;
}