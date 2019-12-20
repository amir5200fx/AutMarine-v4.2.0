#include <SizeMap2d_StdBackSize.hxx>

AutLib::MeshLib::SizeMap2d_StdBackSize::SizeMap2d_StdBackSize
(
	const Standard_Real theBaseSize, 
	const M_GEO GeoMesh_BackGroundMesh2d & BackGround
)
	: SizeMap2d_UniSize(theBaseSize)
	, theMesh_(BackGround)
{
	//Get_Object(Sources) = theMesh_.Sources();
	//Sources *= BaseSize();
}

void AutLib::MeshLib::SizeMap2d_StdBackSize::ExportToPlt(fstream & File) const
{
	theMesh_.ExportToPlt(File);
}