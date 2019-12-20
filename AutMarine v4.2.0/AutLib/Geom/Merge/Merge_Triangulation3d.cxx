#include <Merge_Triangulation3d.hxx>

#include <Entity_Triangulation3d.hxx>
#include <Merge_Pnt3d.hxx>
#include <TColGeom_BasicQueueOfPnt3d.hxx>
#include <TColEntity_BasicQueueOfTriangleIndex.hxx>

using namespace AutLib;
using namespace GeoLib;

AutLib::GeoLib::Merge_Triangulation3d::Merge_Triangulation3d
(
	const Standard_Real Resolution,
	const Standard_Real Radius
)
	: theResolution_(Resolution)
	, theRadius_(Radius)
	, IsDone_(Standard_False)
{
}

AutLib::GeoLib::Merge_Triangulation3d::~Merge_Triangulation3d()
{
	ReleaseMemory();
}

Global_Handle(Entity_Triangulation3d) AutLib::GeoLib::Merge_Triangulation3d::Merged() const
{
	Debug_If_Condition_Message(NOT IsDone_, " Merging NOT performed");

	return theTriangulation_;
}

Standard_Boolean AutLib::GeoLib::Merge_Triangulation3d::IsDone() const
{
	return IsDone_;
}

void AutLib::GeoLib::Merge_Triangulation3d::Import(const TColEntity_HAry1dOfTriangulation3d & theTriangulations)
{
	theTriangulation_ = new Entity_Triangulation3d;

	Debug_Null_Pointer(theTriangulation_);

	Get_Object(Triangulation) = *theTriangulation_;

	TColGeom_BasicQueueOfPnt3d QPoints;
	forThose
	(
		I,
		0,
		MaxIndexOf(theTriangulations)
	)
	{
		Debug_Null_Pointer(theTriangulations[I]);

		Get_Const_Object(Points) = theTriangulations[I]->Points();

		forThose(J, 0, MaxIndexOf(Points))
			QPoints.EnQueue(Points[J]);
	}

	// Import Points to the Triangulation
	QPoints.RetrieveTo(Triangulation.Points());

	Standard_Integer NbPts = 0;

	// Gather Triangles
	TColEntity_BasicQueueOfTriangleIndex QTriangles;
	forThose
	(
		I,
		0,
		MaxIndexOf(theTriangulations)
	)
	{
		Debug_Null_Pointer(theTriangulations[I]);

		Get_Const_Object(Triangles) = theTriangulations[I]->Triangles();

		forThose(J, 0, MaxIndexOf(Triangles))
		{
			QTriangles.EnQueue(Entity_TriangleIndex(Triangles[J].V0() + NbPts, Triangles[J].V1() + NbPts, Triangles[J].V2() + NbPts));
		}
		NbPts += theTriangulations[I]->NbPoints();
	}

	// Import Indices to the Triangulation
	QTriangles.RetrieveTo(Triangulation.Triangles());
}

void AutLib::GeoLib::Merge_Triangulation3d::Perform()
{
	IsDone_ = Standard_True;

	Debug_Null_Pointer(theTriangulation_);

	Get_Object(Triangulation) = *theTriangulation_;

	Merge_Pnt3d Merge(theResolution_, theRadius_);
	Merge.SetCoords(&Triangulation.Points());

	// Merging the points
	Try_Exception_Handle_Exit(Merge.Perform());

	// Import Merged Points to the Triangulation
	Triangulation.Points() = Merge.CompactPoints();

	Get_Const_Object(Indices) = Merge.CompactIndices();

	Get_Object(Triangles) = Triangulation.Triangles();
	forThose
	(
		Index, 
		0, 
		MaxIndexOf(Triangles)
	)
	{
		// Renumbering the Indices
		Try_Exception_Handle_Exit(Triangles[Index].SetValue(Indices[Triangles[Index].V0()], Indices[Triangles[Index].V1()], Indices[Triangles[Index].V2()]));
	}
}

void AutLib::GeoLib::Merge_Triangulation3d::ReleaseMemory()
{
	FreePointer(theTriangulation_);
}