#include <FvmMesh_Node2d.hxx>

AutLib::FvmLib::FvmMesh_Node2d::FvmMesh_Node2d()
{
}

AutLib::FvmLib::FvmMesh_Node2d::FvmMesh_Node2d
(
	const Standard_Integer theIndex,
	const Geom_Pnt2d & theCoord
)
	: theIndex_(theIndex)
	, theCoord_(theCoord)
{
}

void AutLib::FvmLib::FvmMesh_Node2d::Init
(
	const Standard_Integer theIndex,
	const Geom_Pnt2d & theCoord
)
{
	theIndex_ = theIndex;
	theCoord_ = theCoord;
}

void AutLib::FvmLib::FvmMesh_Node2d::SetIndex(const Standard_Integer theIndex)
{
	theIndex_ = theIndex;
}

void AutLib::FvmLib::FvmMesh_Node2d::SetCoord(const Geom_Pnt2d & theCoord)
{
	theCoord_ = theCoord;
}