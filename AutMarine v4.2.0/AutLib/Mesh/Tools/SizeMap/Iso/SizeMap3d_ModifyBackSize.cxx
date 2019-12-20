#include <SizeMap3d_ModifyBackSize.hxx>

static const Standard_Real DEFAULT_Coefficient = 0.3;
static const Standard_Real DEFAULT_Delta = 0.2;

AutLib::MeshLib::SizeMap3d_ModifyBackSize::SizeMap3d_ModifyBackSize
(
	const Standard_Real theBaseSize, 
	const M_GEO GeoMesh_BackGroundMesh3d & theBackGround
)
	: SizeMap3d_StdBackSize(theBaseSize, theBackGround)
	, theCoeff_(DEFAULT_Coefficient)
	, theDelta_(DEFAULT_Delta)
{
}