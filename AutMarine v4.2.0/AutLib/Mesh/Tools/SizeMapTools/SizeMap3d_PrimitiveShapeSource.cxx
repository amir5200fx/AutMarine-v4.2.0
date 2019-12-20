#include <SizeMap3d_PrimitiveShapeSource.hxx>

#include <Global_Debug.hxx>
#include <Geom_Triangulation.hxx>
#include <Entity_Triangulation3d.hxx>
#include <Entity_Tetrahedralization.hxx>
#include <Cad3d_SolidTools.hxx>
#include <TColGeom_Ary1dOfPnt3d.hxx>
#include <TColGeom_BasicQueueOfPnt3d.hxx>

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

using namespace AutLib;
using namespace CadLib;
using namespace GeoLib;

static const Standard_Real DEFAULT_DEFLECTION = 0.1;
static const Standard_Real DEFAULT_ANGLE = 1.0;

namespace AutLib
{
	namespace CadLib
	{

		static Entity_Box3d GetBoundingBox(const Bnd_Box& theBox)
		{
			Standard_Real Xmin, Xmax, Ymin, Ymax, Zmin, Zmax;
			theBox.Get(Xmin, Ymin, Zmin, Xmax, Ymax, Zmax);

			Entity_Box3d Box(Xmin, Xmax, Ymin, Ymax, Zmin, Zmax);
			MOVE(Box);
		}
	}
}

AutLib::MeshLib::SizeMap3d_PrimitiveShapeSource::SizeMap3d_PrimitiveShapeSource()
	: theDeflection_(DEFAULT_DEFLECTION)
	, theAngle_(DEFAULT_ANGLE)
{
}

TopoDS_Shape AutLib::MeshLib::SizeMap3d_PrimitiveShapeSource::Shape() const
{
	return theShape_;
}

void AutLib::MeshLib::SizeMap3d_PrimitiveShapeSource::SetDeflection(const Standard_Real theDeflection)
{
	theDeflection_ = theDeflection;
}

void AutLib::MeshLib::SizeMap3d_PrimitiveShapeSource::SetAngle(const Standard_Real theAngle)
{
	theAngle_ = theAngle;
}

void AutLib::MeshLib::SizeMap3d_PrimitiveShapeSource::SetSize(const Standard_Real theSize)
{
	theSize_ = theSize;
}

void AutLib::MeshLib::SizeMap3d_PrimitiveShapeSource::Box
(
	const Geom_Pnt3d & P,
	const Standard_Real dx, 
	const Standard_Real dy,
	const Standard_Real dz
)
{
	Box(P, Geom_Pnt3d(P.X() + dx, P.Y() + dy, P.Z() + dz));
}

void AutLib::MeshLib::SizeMap3d_PrimitiveShapeSource::Box
(
	const Geom_Pnt3d & P1,
	const Geom_Pnt3d & P2
)
{
	BRepPrimAPI_MakeBox Shape(P1, P2);

	TopoDS_Shape Solid = Shape.Solid().Oriented(TopAbs_Orientation::TopAbs_FORWARD);

	BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = theDeflection_;
	Params.Angle = theAngle_;

	Bnd_Box BoundingBox;
	BRepBndLib::Add(Solid, BoundingBox);

	BRepMesh_FastDiscret Mesh(BoundingBox, Params);
	Mesh.Perform(Solid);

	theShape_ = Solid;

	theBoundingBox_ = GetBoundingBox(BoundingBox);

	//Construct();
}

void AutLib::MeshLib::SizeMap3d_PrimitiveShapeSource::Box
(
	const gp_Ax2 & Axes, 
	const Standard_Real dx,
	const Standard_Real dy, 
	const Standard_Real dz
)
{
	BRepPrimAPI_MakeBox Shape(Geom_Pnt3d(), Geom_Pnt3d(dx, dy, dz));

	TopoDS_Shape Solid = Shape.Solid().Oriented(TopAbs_Orientation::TopAbs_FORWARD);

	BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = theDeflection_;
	Params.Angle = theAngle_;

	Bnd_Box BoundingBox;
	BRepBndLib::Add(Solid, BoundingBox);

	BRepMesh_FastDiscret Mesh(BoundingBox, Params);
	Mesh.Perform(Solid);

	theShape_ = Solid;

	gp_Trsf T;
	T.SetTransformation(Axes);

	BRepBuilderAPI_Transform Transform(T);
	Transform.Perform(theShape_);

	Debug_If_Condition_Message(NOT Transform.IsDone(), "Transformation is not performed");

	theShape_ = Transform.ModifiedShape(theShape_);

	theBoundingBox_ = GetBoundingBox(BoundingBox);

	//Construct();
}

void AutLib::MeshLib::SizeMap3d_PrimitiveShapeSource::Cone
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
	Params.Deflection = theDeflection_;
	Params.Angle = theAngle_;

	Bnd_Box BoundingBox;
	BRepBndLib::Add(Solid, BoundingBox);

	BRepMesh_FastDiscret Mesh(BoundingBox, Params);
	Mesh.Perform(Solid);

	theShape_ = Solid;

	theBoundingBox_ = GetBoundingBox(BoundingBox);

	//Construct();
}

void AutLib::MeshLib::SizeMap3d_PrimitiveShapeSource::Cone
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
	Params.Deflection = theDeflection_;
	Params.Angle = theAngle_;

	Bnd_Box BoundingBox;
	BRepBndLib::Add(Solid, BoundingBox);

	BRepMesh_FastDiscret Mesh(BoundingBox, Params);
	Mesh.Perform(Solid);

	theShape_ = Solid;

	theBoundingBox_ = GetBoundingBox(BoundingBox);

	//Construct();
}

void AutLib::MeshLib::SizeMap3d_PrimitiveShapeSource::Sphere
(
	const Geom_Pnt3d & Center,
	const Standard_Real R
)
{
	BRepPrimAPI_MakeSphere Shape(Center, R);

	TopoDS_Shape Solid = Shape.Solid().Oriented(TopAbs_Orientation::TopAbs_FORWARD);

	BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = theDeflection_;
	Params.Angle = theAngle_;

	Bnd_Box BoundingBox;
	BRepBndLib::Add(Solid, BoundingBox);

	BRepMesh_FastDiscret Mesh(BoundingBox, Params);
	Mesh.Perform(Solid);

	theShape_ = Solid;

	theBoundingBox_ = GetBoundingBox(BoundingBox);

	//Construct();
}

void AutLib::MeshLib::SizeMap3d_PrimitiveShapeSource::Sphere
(
	const gp_Ax2 & Axis, 
	const Standard_Real R
)
{
	BRepPrimAPI_MakeSphere Shape(Axis, R);

	TopoDS_Shape Solid = Shape.Solid().Oriented(TopAbs_Orientation::TopAbs_FORWARD);

	BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = theDeflection_;
	Params.Angle = theAngle_;

	Bnd_Box BoundingBox;
	BRepBndLib::Add(Solid, BoundingBox);

	BRepMesh_FastDiscret Mesh(BoundingBox, Params);
	Mesh.Perform(Solid);

	theShape_ = Solid;

	theBoundingBox_ = GetBoundingBox(BoundingBox);

	//Construct();
}

void AutLib::MeshLib::SizeMap3d_PrimitiveShapeSource::Cylinder
(
	const gp_Ax2 & Axes, 
	const Standard_Real R,
	const Standard_Real H
)
{
	BRepPrimAPI_MakeCylinder Shape(Axes, R, H);

	TopoDS_Shape Solid = Shape.Solid().Oriented(TopAbs_Orientation::TopAbs_FORWARD);

	BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = theDeflection_;
	Params.Angle = theAngle_;

	Bnd_Box BoundingBox;
	BRepBndLib::Add(Solid, BoundingBox);

	BRepMesh_FastDiscret Mesh(BoundingBox, Params);
	Mesh.Perform(Solid);

	theShape_ = Solid;

	theBoundingBox_ = GetBoundingBox(BoundingBox);

	//Construct();
}

void AutLib::MeshLib::SizeMap3d_PrimitiveShapeSource::Cylinder
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
	Params.Deflection = theDeflection_;
	Params.Angle = theAngle_;

	Bnd_Box BoundingBox;
	BRepBndLib::Add(Solid, BoundingBox);

	BRepMesh_FastDiscret Mesh(BoundingBox, Params);
	Mesh.Perform(Solid);

	theShape_ = Solid;

	theBoundingBox_ = GetBoundingBox(BoundingBox);

	//Construct();
}

void AutLib::MeshLib::SizeMap3d_PrimitiveShapeSource::Construct()
{
	TColEntity_HAry1dOfTriangulation3d Triangulations = Cad3d_SolidTools::GetTriangulations(theShape_);

	TColGeom_BasicQueueOfPnt3d QPoints;
	forThose
	(
		Index,
		0, 
		MaxIndexOf(Triangulations)
	)
	{
		Debug_Null_Pointer(Triangulations[Index]);

		Get_Const_Object(Triangulation) = *Triangulations[Index];

		QPoints.EnQueue(Triangulation.Points());
	}
	TColGeom_Ary1dOfPnt3d Points;
	QPoints.RetrieveTo(Points);

	Entity_Tetrahedralization Tetrahedralization;
	Geom_Triangulation::DelaunayTriangulation(Points, &Tetrahedralization);

	theSource_.Mesh().Construct(Tetrahedralization);
	
	Get_Object(Sources) = theSource_.Sources();
	Sources.Resize(Tetrahedralization.NbPoints());
	Sources.Init(theSize_);

	theSource_.InitiateCurrentElement();

	FreeMemory(Triangulations);
}