#include <Mesh2d_NodeTools.hxx>

using namespace AutLib;

TColGeom_Ary1dOfPnt2d AutLib::MeshLib::Mesh2d_NodeTools::GetCoordOf(const TColMesh2d_HAry1dOfNode & Nodes)
{
	TColGeom_Ary1dOfPnt2d Points(Nodes.Size());
	forThose
	(
		Index,
		0, 
		MaxIndexOf(Points)
	)
	{
		Debug_Null_Pointer(Nodes[Index]);

		Points[Index] = Nodes[Index]->Coord();
	}
	MOVE(Points);
}