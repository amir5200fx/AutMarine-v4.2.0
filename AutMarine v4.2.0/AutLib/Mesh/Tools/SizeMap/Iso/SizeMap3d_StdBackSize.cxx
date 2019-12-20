#include <SizeMap3d_StdBackSize.hxx>

AutLib::MeshLib::SizeMap3d_StdBackSize::SizeMap3d_StdBackSize
(
	const Standard_Real BaseSize,
	const M_GEO GeoMesh_BackGroundMesh3d & BackGround
)
	: SizeMap3d_UniSize(BaseSize)
	, theMesh_(BackGround)
{
	// Empty constructor
}

void AutLib::MeshLib::SizeMap3d_StdBackSize::ExportToPlt(fstream & File) const
{
	theMesh_.ExportToPlt(File);
}

void AutLib::MeshLib::SizeMap3d_StdBackSize::ExportSizeMapToPlt(fstream & File) const
{
	theMesh_.ExportToPlt(File);
}