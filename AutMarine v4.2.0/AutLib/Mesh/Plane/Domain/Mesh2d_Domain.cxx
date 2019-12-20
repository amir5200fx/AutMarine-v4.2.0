#include "Mesh2d_Domain.hxx"

#include <Cad2d_CurveOnPlane.hxx>
#include <Cad2d_EdgeOnPlane.hxx>
#include <Cad2d_Plane.hxx>
#include <Geom2d_Curve.hxx>
#include <TColEntity_HAry1dOfStaticChain2d.hxx>
#include <Mesh2d_Curve.hxx>
#include <Merge_Chain2d.hxx>
#include <Entity_StaticChain2d.hxx>
#include <Geometry_Tools.hxx>

using namespace AutLib;
using namespace GeoLib;

static const Standard_Real Resolution = 1.0E-3;
static const Standard_Real Radius = 1.0E-6;
static const Standard_Real DEFAULT_DEGENERACY = 1.0E-6;

AutLib::MeshLib::Mesh2d_Domain::Mesh2d_Domain()
	: theMap_(0)
	, thePlane_(0)
	, theResolution_(Resolution)
	, theRadius_(Radius)
	, theDegeneracy_(DEFAULT_DEGENERACY)
	, IsDone_(Standard_False)
{
}

AutLib::MeshLib::Mesh2d_Domain::Mesh2d_Domain
(
	const Mesh2d_SizeMap & SizeMap,
	const Global_Handle(M_CAD Cad2d_Plane) Plane,
	const Standard_Real Tolerance
)
	: theMap_(&SizeMap)
	, thePlane_(Plane)
	, theResolution_(Resolution)
	, theRadius_(Tolerance)
	, IsDone_(Standard_False)
{
}

AutLib::MeshLib::Mesh2d_Domain::~Mesh2d_Domain()
{
	FreeMemory(theMeshCurves_);
}

void AutLib::MeshLib::Mesh2d_Domain::SetCCWorder()
{
	if (NOT Geometry_Tools::IsCcwOrder(theChain_.Coords()))
	{
		theChain_.Reverse();
	}
}

void AutLib::MeshLib::Mesh2d_Domain::SetTolerance(const Standard_Real Tolerance)
{
	theRadius_ = Tolerance;
}

void AutLib::MeshLib::Mesh2d_Domain::SetSizeMap(const Mesh2d_SizeMap & SizeMap)
{
	theMap_ = &SizeMap;
}

void AutLib::MeshLib::Mesh2d_Domain::SetPlane(const Global_Handle(M_CAD Cad2d_Plane) Plane)
{
	thePlane_ = Plane;
}

void AutLib::MeshLib::Mesh2d_Domain::Perform(Standard_Boolean doMerging)
{
	IsDone_ = Standard_True;

	Debug_Null_Pointer(theMap_);
	Debug_Null_Pointer(thePlane_);

	Get_Const_Object(Map) = *theMap_;
	Get_Const_Object(Plane) = *thePlane_;

	TColCad2d_HAry1dOfCurveOnPlane CurvesOnPlane;
	Plane.RetrieveCurvesTo(CurvesOnPlane);

	const Standard_Integer NbCurves = CurvesOnPlane.Size();
	if (NbCurves < 1) { THROW_STANDARD_EXCEPTION("The plane has no curve"); }

	theMeshCurves_.Resize(NbCurves);

	forThose
	(
		Index, 
		0, 
		MaxIndexOf(CurvesOnPlane)
	)
	{
		Debug_Null_Pointer(CurvesOnPlane[Index]);

		theMeshCurves_[Index] = new Mesh2d_Curve(Map, CurvesOnPlane[Index]);

		Try_Exception_Handle_Exit(theMeshCurves_[Index]->Perform());

		Debug_If_Condition_Message(NOT theMeshCurves_[Index]->IsDone(), " Curve Not discretized");
	}

	if (doMerging) Merging();
}

void AutLib::MeshLib::Mesh2d_Domain::ExportCurveMeshToPlt(fstream & File) const
{
	forThose
	(
		Index, 
		0, 
		MaxIndexOf(theMeshCurves_)
	)
	{
		theMeshCurves_[Index]->ExportToPlt(File);
	}
}

void AutLib::MeshLib::Mesh2d_Domain::ExportMergedToPlt(fstream & File) const
{
	theChain_.ExportToPlt(File);
}

void AutLib::MeshLib::Mesh2d_Domain::Merging()
{
	TColEntity_HAry1dOfStaticChain2d Chains(theMeshCurves_.Size());

	forThose
	(
		Index,
		0, 
		MaxIndexOf(Chains)
	)
	{
		Debug_Null_Pointer(theMeshCurves_[Index]);

		Chains[Index] = (Global_Handle(M_GEO Entity_StaticChain2d))&theMeshCurves_[Index]->Chain();
	}
	
	M_GEO Merge_Chain2d Merge(theResolution_, theRadius_);
	Merge.Import(Chains);
	Merge.Perform();
	
	Debug_If_Condition_Message(NOT Merge.IsDone(), " Merging is not Performed");

	theChain_ = *Merge.Merged();
}

//void AutLib::MeshLib::Mesh2d_Domain::RemoveDegeneracy() const
//{
//
//}