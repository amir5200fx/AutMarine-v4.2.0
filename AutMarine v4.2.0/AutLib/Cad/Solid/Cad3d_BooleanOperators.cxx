#include <Cad3d_BooleanOperators.hxx>

#include <Cad3d_Solid.hxx>
#include <Cad3d_SolidTools.hxx>

using namespace AutLib;
using namespace CadLib;

#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Common.hxx>
#include <TopoDS_Shape.hxx>
#include <Bnd_Box.hxx>
#include <BRepBndLib.hxx>
#include <TopoDS_Shape.hxx>
#include <BRepMesh_FastDiscret.hxx>

TopoDS_Shape AutLib::CadLib::Cad3d_BooleanOperators::Union
(
	const TopoDS_Shape & theSolid1,
	const TopoDS_Shape & theSolid2
)
{
	TopoDS_Shape Sum = BRepAlgoAPI_Fuse(theSolid1, theSolid2);

	/*BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = 0.1;
	Params.Angle = 1.0;

	Bnd_Box BoundingBox;
	BRepBndLib::Add(Sum, BoundingBox);

	BRepMesh_FastDiscret Mesh(BoundingBox, Params);
	Mesh.Perform(Sum);*/

	return Sum;
}

TopoDS_Shape AutLib::CadLib::Cad3d_BooleanOperators::Subtract
(
	const TopoDS_Shape & theTarget, 
	const TopoDS_Shape & theSolid
)
{
	TopoDS_Shape Sum = BRepAlgoAPI_Cut(theTarget, theSolid);

	/*BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = 0.1;
	Params.Angle = 1.0;

	Bnd_Box BoundingBox;
	BRepBndLib::Add(Sum, BoundingBox);

	BRepMesh_FastDiscret Mesh(BoundingBox, Params);
	Mesh.Perform(Sum);*/

	return Sum;
}

TopoDS_Shape AutLib::CadLib::Cad3d_BooleanOperators::Intersect
(
	const TopoDS_Shape & theSolid1, 
	const TopoDS_Shape & theSolid2
)
{
	TopoDS_Shape Sum = BRepAlgoAPI_Common(theSolid1, theSolid2);

	/*BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = 0.1;
	Params.Angle = 1.0;

	Bnd_Box BoundingBox;
	BRepBndLib::Add(Sum, BoundingBox);

	BRepMesh_FastDiscret Mesh(BoundingBox, Params);
	Mesh.Perform(Sum);*/

	return Sum;
}