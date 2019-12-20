#include <FvEntity_Node2d.hxx>

AutLib::FvLib::FvEntity_Node2d::FvEntity_Node2d()
{
}

AutLib::FvLib::FvEntity_Node2d::FvEntity_Node2d
(
	const Standard_Integer theIndex,
	const Geom_Pnt2d & theCoord
)
	: theIndex_(theIndex)
	, theCoord_(theCoord)
{
}

void AutLib::FvLib::FvEntity_Node2d::SetCoord(const Geom_Pnt2d & theCoord)
{
	theCoord_ = theCoord;
}

void AutLib::FvLib::FvEntity_Node2d::SetIndex(const Standard_Integer theIndex)
{
	theIndex_ = theIndex;
}

void AutLib::FvLib::FvEntity_Node2d::ImportElement(const Global_Handle(FvEntity_Element2d) theElement)
{
	theElements_.EnQueue((Global_Handle(FvEntity_Element2d))theElement);
}