#include <Cad3d_MakeSolid.hxx>

#include <Cad3d_SolidTools.hxx>

#include <gp_Trsf.hxx>
#include <gp_Ax2.hxx>
#include <gp_Ax3.hxx>
#include <Bnd_Box.hxx>
#include <BRepBndLib.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepMesh_FastDiscret.hxx>

TopoDS_Shape AutLib::CadLib::Cad3d_MakeSolid::Box
(
	const Geom_Pnt3d & P,
	const Standard_Real dx, 
	const Standard_Real dy,
	const Standard_Real dz
)
{
	return Box(P, Geom_Pnt3d(P.X() + dx, P.Y() + dy, P.Z() + dz));
}

TopoDS_Shape AutLib::CadLib::Cad3d_MakeSolid::Box
(
	const Geom_Pnt3d & P1,
	const Geom_Pnt3d & P2
)
{
	BRepPrimAPI_MakeBox Shape(P1, P2);

	TopoDS_Shape Solid = Shape.Solid().Oriented(TopAbs_Orientation::TopAbs_FORWARD);

	BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = 0.1;
	Params.Angle = 1.0;

	Bnd_Box BoundingBox;
	BRepBndLib::Add(Solid, BoundingBox);

	BRepMesh_FastDiscret Mesh(BoundingBox, Params);
	Mesh.Perform(Solid);

	return Solid;
}

TopoDS_Shape AutLib::CadLib::Cad3d_MakeSolid::Box
(
	const gp_Ax2 & Axes,
	const Standard_Real dx, 
	const Standard_Real dy, 
	const Standard_Real dz
)
{
	TopoDS_Shape Shape = Box(Geom_Pnt3d(), dx, dy, dz);

	gp_Trsf T;
	T.SetTransformation(Axes);

	BRepBuilderAPI_Transform Transform(T);
	Transform.Perform(Shape);

	Debug_If_Condition_Message(NOT Transform.IsDone(), "Transformation is not performed");

	return Transform.ModifiedShape(Shape);
}

TopoDS_Shape AutLib::CadLib::Cad3d_MakeSolid::Cone
(
	const Standard_Real R1, 
	const Standard_Real R2, 
	const Standard_Real H
)
{
	BRepPrimAPI_MakeCone Shape(R1, R2, H);

	TopoDS_Shape Solid = Shape.Solid().Oriented(TopAbs_Orientation::TopAbs_FORWARD);

	BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = 0.1;
	Params.Angle = 1.0;

	Bnd_Box BoundingBox;
	BRepBndLib::Add(Solid, BoundingBox);

	BRepMesh_FastDiscret Mesh(BoundingBox, Params);
	Mesh.Perform(Solid);

	return Solid;
}

TopoDS_Shape AutLib::CadLib::Cad3d_MakeSolid::Cone
(
	const gp_Ax2 & Axes,
	const Standard_Real R1, 
	const Standard_Real R2, 
	const Standard_Real H
)
{
	BRepPrimAPI_MakeCone Shape(Axes, R1, R2, H);

	TopoDS_Shape Solid = Shape.Solid().Oriented(TopAbs_Orientation::TopAbs_FORWARD);

	BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = 0.1;
	Params.Angle = 1.0;

	Bnd_Box BoundingBox;
	BRepBndLib::Add(Solid, BoundingBox);

	BRepMesh_FastDiscret Mesh(BoundingBox, Params);
	Mesh.Perform(Solid);

	return Solid;
}

TopoDS_Shape AutLib::CadLib::Cad3d_MakeSolid::Cone
(
	const gp_Ax2 & Axes,
	const Standard_Real R1,
	const Standard_Real R2,
	const Standard_Real H, 
	const Standard_Real angle
)
{
	BRepPrimAPI_MakeCone Shape(Axes, R1, R2, H, angle);

	TopoDS_Shape Solid = Shape.Solid().Oriented(TopAbs_Orientation::TopAbs_FORWARD);

	BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = 0.1;
	Params.Angle = 1.0;

	Bnd_Box BoundingBox;
	BRepBndLib::Add(Solid, BoundingBox);

	BRepMesh_FastDiscret Mesh(BoundingBox, Params);
	Mesh.Perform(Solid);

	return Solid;
}

TopoDS_Shape AutLib::CadLib::Cad3d_MakeSolid::Sphere
(
	const Geom_Pnt3d & Center,
	const Standard_Real R
)
{
	BRepPrimAPI_MakeSphere Shape(Center, R);

	TopoDS_Shape Solid = Shape.Solid().Oriented(TopAbs_Orientation::TopAbs_FORWARD);

	BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = 0.1;
	Params.Angle = 1.0;

	Bnd_Box BoundingBox;
	BRepBndLib::Add(Solid, BoundingBox);

	BRepMesh_FastDiscret Mesh(BoundingBox, Params);
	Mesh.Perform(Solid);

	return Solid;
}

TopoDS_Shape AutLib::CadLib::Cad3d_MakeSolid::Sphere
(
	const Geom_Pnt3d & Center, 
	const Standard_Real R,
	const Standard_Real angle
)
{
	BRepPrimAPI_MakeSphere Shape(Center, R, angle);

	TopoDS_Shape Solid = Shape.Solid().Oriented(TopAbs_Orientation::TopAbs_FORWARD);

	BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = 0.1;
	Params.Angle = 1.0;

	Bnd_Box BoundingBox;
	BRepBndLib::Add(Solid, BoundingBox);

	BRepMesh_FastDiscret Mesh(BoundingBox, Params);
	Mesh.Perform(Solid);

	return Solid;
}

TopoDS_Shape AutLib::CadLib::Cad3d_MakeSolid::Sphere
(
	const Geom_Pnt3d & Center, 
	const Standard_Real R,
	const Standard_Real angle1, 
	const Standard_Real angle2
)
{
	BRepPrimAPI_MakeSphere Shape(Center, R, angle1, angle2);

	TopoDS_Shape Solid = Shape.Solid().Oriented(TopAbs_Orientation::TopAbs_FORWARD);

	BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = 0.1;
	Params.Angle = 1.0;

	Bnd_Box BoundingBox;
	BRepBndLib::Add(Solid, BoundingBox);

	BRepMesh_FastDiscret Mesh(BoundingBox, Params);
	Mesh.Perform(Solid);

	return Solid;
}

TopoDS_Shape AutLib::CadLib::Cad3d_MakeSolid::Sphere
(
	const Geom_Pnt3d & Center, 
	const Standard_Real R, 
	const Standard_Real angle1,
	const Standard_Real angle2,
	const Standard_Real angle3
)
{
	BRepPrimAPI_MakeSphere Shape(Center, R, angle1, angle2, angle3);

	TopoDS_Shape Solid = Shape.Solid().Oriented(TopAbs_Orientation::TopAbs_FORWARD);

	BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = 0.1;
	Params.Angle = 1.0;

	Bnd_Box BoundingBox;
	BRepBndLib::Add(Solid, BoundingBox);

	BRepMesh_FastDiscret Mesh(BoundingBox, Params);
	Mesh.Perform(Solid);

	return Solid;
}

TopoDS_Shape AutLib::CadLib::Cad3d_MakeSolid::Sphere
(
	const gp_Ax2 & Axis, 
	const Standard_Real R
)
{
	BRepPrimAPI_MakeSphere Shape(Axis, R);

	TopoDS_Shape Solid = Shape.Solid().Oriented(TopAbs_Orientation::TopAbs_FORWARD);

	BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = 0.1;
	Params.Angle = 1.0;

	Bnd_Box BoundingBox;
	BRepBndLib::Add(Solid, BoundingBox);

	BRepMesh_FastDiscret Mesh(BoundingBox, Params);
	Mesh.Perform(Solid);

	return Solid;
}

TopoDS_Shape AutLib::CadLib::Cad3d_MakeSolid::Sphere
(
	const gp_Ax2 & Axis,
	const Standard_Real R, 
	const Standard_Real angle
)
{
	BRepPrimAPI_MakeSphere Shape(Axis, R, angle);

	TopoDS_Shape Solid = Shape.Solid().Oriented(TopAbs_Orientation::TopAbs_FORWARD);

	BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = 0.1;
	Params.Angle = 1.0;

	Bnd_Box BoundingBox;
	BRepBndLib::Add(Solid, BoundingBox);

	BRepMesh_FastDiscret Mesh(BoundingBox, Params);
	Mesh.Perform(Solid);

	return Solid;
}

TopoDS_Shape AutLib::CadLib::Cad3d_MakeSolid::Sphere
(
	const gp_Ax2 & Axis, 
	const Standard_Real R,
	const Standard_Real angle1,
	const Standard_Real angle2
)
{
	BRepPrimAPI_MakeSphere Shape(Axis, R, angle1, angle2);

	TopoDS_Shape Solid = Shape.Solid().Oriented(TopAbs_Orientation::TopAbs_FORWARD);

	BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = 0.1;
	Params.Angle = 1.0;

	Bnd_Box BoundingBox;
	BRepBndLib::Add(Solid, BoundingBox);

	BRepMesh_FastDiscret Mesh(BoundingBox, Params);
	Mesh.Perform(Solid);

	return Solid;
}

TopoDS_Shape AutLib::CadLib::Cad3d_MakeSolid::Sphere
(
	const gp_Ax2 & Axis,
	const Standard_Real R, 
	const Standard_Real angle1, 
	const Standard_Real angle2, 
	const Standard_Real angle3
)
{
	BRepPrimAPI_MakeSphere Shape(Axis, R, angle1, angle2, angle3);

	TopoDS_Shape Solid = Shape.Solid().Oriented(TopAbs_Orientation::TopAbs_FORWARD);

	BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = 0.1;
	Params.Angle = 1.0;

	Bnd_Box BoundingBox;
	BRepBndLib::Add(Solid, BoundingBox);

	BRepMesh_FastDiscret Mesh(BoundingBox, Params);
	Mesh.Perform(Solid);

	return Solid;
}

TopoDS_Shape AutLib::CadLib::Cad3d_MakeSolid::Cylinder
(
	const Standard_Real R,
	const Standard_Real H
)
{
	BRepPrimAPI_MakeCylinder Shape(R, H);

	TopoDS_Shape Solid = Shape.Solid().Oriented(TopAbs_Orientation::TopAbs_FORWARD);

	BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = 0.1;
	Params.Angle = 1.0;

	Bnd_Box BoundingBox;
	BRepBndLib::Add(Solid, BoundingBox);

	BRepMesh_FastDiscret Mesh(BoundingBox, Params);
	Mesh.Perform(Solid);

	return Solid;
}

TopoDS_Shape AutLib::CadLib::Cad3d_MakeSolid::Cylinder
(
	const Standard_Real R, 
	const Standard_Real H, 
	const Standard_Real Angle
)
{
	BRepPrimAPI_MakeCylinder Shape(R, H, Angle);

	TopoDS_Shape Solid = Shape.Solid().Oriented(TopAbs_Orientation::TopAbs_FORWARD);

	BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = 0.1;
	Params.Angle = 1.0;

	Bnd_Box BoundingBox;
	BRepBndLib::Add(Solid, BoundingBox);

	BRepMesh_FastDiscret Mesh(BoundingBox, Params);
	Mesh.Perform(Solid);

	return Solid;
}

TopoDS_Shape AutLib::CadLib::Cad3d_MakeSolid::Cylinder
(
	const gp_Ax2 & Axes,
	const Standard_Real R, 
	const Standard_Real H
)
{
	BRepPrimAPI_MakeCylinder Shape(Axes, R, H);

	TopoDS_Shape Solid = Shape.Solid().Oriented(TopAbs_Orientation::TopAbs_FORWARD);

	BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = 0.1;
	Params.Angle = 1.0;

	Bnd_Box BoundingBox;
	BRepBndLib::Add(Solid, BoundingBox);

	BRepMesh_FastDiscret Mesh(BoundingBox, Params);
	Mesh.Perform(Solid);

	return Solid;
}

TopoDS_Shape AutLib::CadLib::Cad3d_MakeSolid::Cylinder
(
	const gp_Ax2 & Axes, 
	const Standard_Real R, 
	const Standard_Real H, 
	const Standard_Real Angle
)
{
	BRepPrimAPI_MakeCylinder Shape(Axes, R, H, Angle);

	TopoDS_Shape Solid = Shape.Solid().Oriented(TopAbs_Orientation::TopAbs_FORWARD);

	BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = 0.1;
	Params.Angle = 1.0;

	Bnd_Box BoundingBox;
	BRepBndLib::Add(Solid, BoundingBox);

	BRepMesh_FastDiscret Mesh(BoundingBox, Params);
	Mesh.Perform(Solid);

	return Solid;
}

TopoDS_Shape AutLib::CadLib::Cad3d_MakeSolid::Torus
(
	const Standard_Real R1, 
	const Standard_Real R2
)
{
	BRepPrimAPI_MakeTorus Shape(R1, R2);

	TopoDS_Shape Solid = Shape.Solid().Oriented(TopAbs_Orientation::TopAbs_FORWARD);

	BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = 0.1;
	Params.Angle = 1.0;

	Bnd_Box BoundingBox;
	BRepBndLib::Add(Solid, BoundingBox);

	BRepMesh_FastDiscret Mesh(BoundingBox, Params);
	Mesh.Perform(Solid);

	return Solid;
}

TopoDS_Shape AutLib::CadLib::Cad3d_MakeSolid::Torus
(
	const Standard_Real R1,
	const Standard_Real R2, 
	const Standard_Real angle
)
{
	BRepPrimAPI_MakeTorus Shape(R1, R2, angle);

	TopoDS_Shape Solid = Shape.Solid().Oriented(TopAbs_Orientation::TopAbs_FORWARD);

	BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = 0.1;
	Params.Angle = 1.0;

	Bnd_Box BoundingBox;
	BRepBndLib::Add(Solid, BoundingBox);

	BRepMesh_FastDiscret Mesh(BoundingBox, Params);
	Mesh.Perform(Solid);

	return Solid;
}

TopoDS_Shape AutLib::CadLib::Cad3d_MakeSolid::Torus
(
	const Standard_Real R1, 
	const Standard_Real R2, 
	const Standard_Real angle1,
	const Standard_Real angle2
)
{
	BRepPrimAPI_MakeTorus Shape(R1, R2, angle1, angle2);

	TopoDS_Shape Solid = Shape.Solid().Oriented(TopAbs_Orientation::TopAbs_FORWARD);

	BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = 0.1;
	Params.Angle = 1.0;

	Bnd_Box BoundingBox;
	BRepBndLib::Add(Solid, BoundingBox);

	BRepMesh_FastDiscret Mesh(BoundingBox, Params);
	Mesh.Perform(Solid);

	return Solid;
}

TopoDS_Shape AutLib::CadLib::Cad3d_MakeSolid::Torus
(
	const Standard_Real R1, 
	const Standard_Real R2, 
	const Standard_Real angle1,
	const Standard_Real angle2,
	const Standard_Real angle
)
{
	BRepPrimAPI_MakeTorus Shape(R1, R2, angle1, angle2, angle);

	TopoDS_Shape Solid = Shape.Solid().Oriented(TopAbs_Orientation::TopAbs_FORWARD);

	BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = 0.1;
	Params.Angle = 1.0;

	Bnd_Box BoundingBox;
	BRepBndLib::Add(Solid, BoundingBox);

	BRepMesh_FastDiscret Mesh(BoundingBox, Params);
	Mesh.Perform(Solid);

	return Solid;
}

TopoDS_Shape AutLib::CadLib::Cad3d_MakeSolid::Torus
(
	const gp_Ax2 & Axes, 
	const Standard_Real R1, 
	const Standard_Real R2
)
{
	BRepPrimAPI_MakeTorus Shape(Axes, R1, R2);

	TopoDS_Shape Solid = Shape.Solid().Oriented(TopAbs_Orientation::TopAbs_FORWARD);

	BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = 0.1;
	Params.Angle = 1.0;

	Bnd_Box BoundingBox;
	BRepBndLib::Add(Solid, BoundingBox);

	BRepMesh_FastDiscret Mesh(BoundingBox, Params);
	Mesh.Perform(Solid);

	return Solid;
}

TopoDS_Shape AutLib::CadLib::Cad3d_MakeSolid::Torus
(
	const gp_Ax2 & Axes, 
	const Standard_Real R1, 
	const Standard_Real R2, 
	const Standard_Real angle
)
{
	BRepPrimAPI_MakeTorus Shape(Axes, R1, R2, angle);

	TopoDS_Shape Solid = Shape.Solid().Oriented(TopAbs_Orientation::TopAbs_FORWARD);

	BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = 0.1;
	Params.Angle = 1.0;

	Bnd_Box BoundingBox;
	BRepBndLib::Add(Solid, BoundingBox);

	BRepMesh_FastDiscret Mesh(BoundingBox, Params);
	Mesh.Perform(Solid);

	return Solid;
}

TopoDS_Shape AutLib::CadLib::Cad3d_MakeSolid::Torus
(
	const gp_Ax2 & Axes,
	const Standard_Real R1,
	const Standard_Real R2,
	const Standard_Real angle1,
	const Standard_Real angle2
)
{
	BRepPrimAPI_MakeTorus Shape(Axes, R1, R2, angle1, angle2);

	TopoDS_Shape Solid = Shape.Solid().Oriented(TopAbs_Orientation::TopAbs_FORWARD);

	BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = 0.1;
	Params.Angle = 1.0;

	Bnd_Box BoundingBox;
	BRepBndLib::Add(Solid, BoundingBox);

	BRepMesh_FastDiscret Mesh(BoundingBox, Params);
	Mesh.Perform(Solid);

	return Solid;
}

TopoDS_Shape AutLib::CadLib::Cad3d_MakeSolid::Torus
(
	const gp_Ax2 & Axes,
	const Standard_Real R1,
	const Standard_Real R2, 
	const Standard_Real angle1,
	const Standard_Real angle2,
	const Standard_Real angle
)
{
	BRepPrimAPI_MakeTorus Shape(Axes, R1, R2, angle1, angle2, angle);

	TopoDS_Shape Solid = Shape.Solid().Oriented(TopAbs_Orientation::TopAbs_FORWARD);

	return Solid;
}