#include <FvmMesh_TriElement2d.hxx>

AutLib::FvmLib::FvmMesh_TriElement2d::FvmMesh_TriElement2d()
{
}

AutLib::FvmLib::FvmMesh_TriElement2d::FvmMesh_TriElement2d
(
	const Global_Handle(FvmMesh_Node2d) theNode0,
	const Global_Handle(FvmMesh_Node2d) theNode1,
	const Global_Handle(FvmMesh_Node2d) theNode2,
	const Global_Handle(FvmMesh_Face2d) theFace0,
	const Global_Handle(FvmMesh_Face2d) theFace1,
	const Global_Handle(FvmMesh_Face2d) theFace2
)
	: theNode0_(theNode0)
	, theNode1_(theNode1)
	, theNode2_(theNode2)
	, theFace0_(theFace0)
	, theFace1_(theFace1)
	, theFace2_(theFace2)
{
}

void AutLib::FvmLib::FvmMesh_TriElement2d::Init
(
	const Global_Handle(FvmMesh_Node2d) theNode0,
	const Global_Handle(FvmMesh_Node2d) theNode1,
	const Global_Handle(FvmMesh_Node2d) theNode2,
	const Global_Handle(FvmMesh_Face2d) theFace0,
	const Global_Handle(FvmMesh_Face2d) theFace1,
	const Global_Handle(FvmMesh_Face2d) theFace2
)
{
	theNode0_ = theNode0;
	theNode1_ = theNode1;
	theNode2_ = theNode2;

	theFace0_ = theFace0;
	theFace1_ = theFace1;
	theFace2_ = theFace2;
}