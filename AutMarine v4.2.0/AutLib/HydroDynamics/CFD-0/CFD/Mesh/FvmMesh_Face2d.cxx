#include <FvmMesh_Face2d.hxx>

AutLib::FvmLib::FvmMesh_Face2d::FvmMesh_Face2d()
{
}

AutLib::FvmLib::FvmMesh_Face2d::FvmMesh_Face2d
(
	const Standard_Integer theIndex,
	const Global_Handle(FvmMesh_Node2d) theNode0,
	const Global_Handle(FvmMesh_Node2d) theNode1
)
	: theIndex_(theIndex)
	, theNode0_(theNode0)
	, theNode1_(theNode1)
{
}

void AutLib::FvmLib::FvmMesh_Face2d::Init
(
	const Standard_Integer theIndex,
	const Global_Handle(FvmMesh_Node2d) theNode0,
	const Global_Handle(FvmMesh_Node2d) theNode1
)
{
	theIndex_ = theIndex;
	theNode0_ = theNode0;
	theNode1_ = theNode1;
}

void AutLib::FvmLib::FvmMesh_Face2d::SetElement(const Global_Handle(FvmMesh_Element2d) theElement)
{
	theElement_ = theElement;
}

void AutLib::FvmLib::FvmMesh_Face2d::SetPair(const Global_Handle(FvmMesh_Face2d) thePair)
{
	thePair_ = thePair;
}