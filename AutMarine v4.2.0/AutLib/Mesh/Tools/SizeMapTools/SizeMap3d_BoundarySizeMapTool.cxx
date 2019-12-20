#include <SizeMap3d_BoundarySizeMapTool.hxx>

#include <Cad3d_Solid.hxx>
#include <Cad3d_BlockEntityOnSolid.hxx>
#include <Mesh_ReferenceValues.hxx>
#include <TColCad3d_HBasicQueueOfEntityOnSolid.hxx>

using namespace AutLib;
using namespace GeoLib;
using namespace CadLib;

AutLib::MeshLib::SizeMap3d_BoundarySizeMapTool::~SizeMap3d_BoundarySizeMapTool()
{
}

AutLib::MeshLib::SizeMap3d_BoundarySizeMapTool::SizeMap3d_BoundarySizeMapTool
(
	const Global_Handle(Mesh_ReferenceValues) theReference,
	const Global_Handle(M_CAD Cad3d_Solid) theSolid
)
	: SizeMap3d_SizeMapTool(theReference, theSolid)
{
}

void AutLib::MeshLib::SizeMap3d_BoundarySizeMapTool::RetrieveEntitiesTo(TColCad3d_HAry1dOfEntityOnSolid & theEntities) const
{
	CloseProgram("SizeMap3d_BoundarySizeMapTool::RetrieveEntitiesTo: Not supposed to call");
}