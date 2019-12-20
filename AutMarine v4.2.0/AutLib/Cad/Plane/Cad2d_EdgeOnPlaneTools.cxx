#include <Cad2d_EdgeOnPlaneTools.hxx>

#include <Entity_EdgeIndexTools.hxx>
#include <Entity_StaticChain2d.hxx>
#include <Cad2d_PointOnPlane.hxx>
#include <Cad2d_CurveOnPlane.hxx>
#include <Cad2d_EdgeOnPlane.hxx>
#include <Cad2d_RingOnPlane.hxx>
#include <Cad2d_PointOnPlaneTools.hxx>
#include <TColCad2d_HNumbAvlTreeOfPointOnPlane.hxx>
#include <TColStd_BasicQueueOfReal.hxx>
#include <TColCad2d_HAry1dOfPointOnPlane.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace GeoLib;

TColCad2d_HAry1dOfCurveOnPlane AutLib::CadLib::Cad2d_EdgeOnPlaneTools::RetrieveCurvesFrom(const TColCad2d_HAry1dOfEdgeOnPlane & theEdges)
{
	TColCad2d_HAry1dOfCurveOnPlane Curves(theEdges.Size());
	forThose
	(
		Index,
		0, 
		MaxIndexOf(theEdges)
	)
	{
		Debug_Null_Pointer(theEdges[Index]);

		Curves[Index] = theEdges[Index]->Curve();
	}
	MOVE(Curves);
}

TColCad2d_HAry1dOfPointOnPlane AutLib::CadLib::Cad2d_EdgeOnPlaneTools::RetrievePointsFrom(const TColCad2d_HAry1dOfEdgeOnPlane & theEdges)
{
	TColCad2d_HNumbAvlTreeOfPointOnPlane Compact;
	Compact.SetComparable(&Cad2d_PointOnPlaneTools::IsLess);

	forThose
	(
		Index, 
		0, 
		MaxIndexOf(theEdges)
	)
	{
		Debug_Null_Pointer(theEdges[Index]);
		Try_Exception_Handle_Exit(Compact.InsertIgnoreDup((Global_Handle(Cad2d_PointOnPlane))theEdges[Index]->FirstPoint()));
		Try_Exception_Handle_Exit(Compact.InsertIgnoreDup((Global_Handle(Cad2d_PointOnPlane))theEdges[Index]->LastPoint()));
	}
	TColCad2d_HAry1dOfPointOnPlane Points;
	Compact.RetrieveTo(Points);
	MOVE(Points);
}

TColCad2d_HAry1dOfEdgeOnPlane AutLib::CadLib::Cad2d_EdgeOnPlaneTools::MakeEdges
(
	const TColCad2d_HAry1dOfCurveOnPlane & theCurves,
	const Standard_Real theTolerance
)
{
	if (theCurves.Size() < 1) { THROW_STANDARD_EXCEPTION("Empty list"); }

	TColCad2d_HAry1dOfEdgeOnPlane Created;
	if (theCurves.Size() EQUAL 1)
	{
		Debug_Null_Pointer(theCurves[0]);

		Get_Const_Object(Curve) = *theCurves[0];
		if (NOT Curve.IsClosed(theTolerance)) { THROW_STANDARD_EXCEPTION(" Not closed wire"); }

		Global_Handle(Cad2d_PointOnPlane) Point = new Cad2d_PointOnPlane(1, Curve.FirstCoord());
		Global_Handle(Cad2d_RingOnPlane) Edge = new Cad2d_RingOnPlane(1, Point, theCurves[0]);

		Point->ImportEdge(Edge);

		Created.Resize(1);
		Created[0] = Edge;
		MOVE(Created);
	}
	
	Standard_Integer K = 0;
	TColGeom_Ary1dOfPnt2d Coords(theCurves.Size() * 2);
	forThose
	(
		Index,
		0,
		MaxIndexOf(theCurves)
	)
	{
		Debug_Null_Pointer(theCurves[Index]);
		Get_Const_Object(Curve) = *theCurves[Index];

		Coords[K] = Curve.FirstCoord();
		K++;

		Coords[K] = Curve.LastCoord();
		K++;
	}

	Entity_StaticChain2d Chain;
	Chain.Init(Coords, Entity_EdgeIndexTools::DiscreteOrderedList(theCurves.Size()));
	
	Chain.Merging(Standard_False);

	Get_Const_Object(MergedCoords) = Chain.Coords();
	Get_Const_Object(MergedEdges) = Chain.Edges();

	TColCad2d_HAry1dOfPointOnPlane Pts(MergedCoords.Size());
	forThose(Index, 0, MaxIndexOf(Pts))
		Pts[Index] = new Cad2d_PointOnPlane(Index + 1, MergedCoords[Index]);

	TColCad2d_HAry1dOfEdgeOnPlane Edges(MergedEdges.Size());
	forThose
	(
		Index,
		0,
		MaxIndexOf(MergedEdges)
	)
	{
		Get_Const_Object(Edge) = MergedEdges[Index];

		if (Edge.V0() EQUAL Edge.V1())
		{
			Edges[Index] = new Cad2d_RingOnPlane(Index + 1, Pts[Index_Of(Edge.V0())], theCurves[Index]);

			Try_Exception_Handle_Exit(Pts[Index_Of(Edge.V0())]->ImportEdge(Edges[Index]));
		}
		else
		{
			Edges[Index] = new Cad2d_EdgeOnPlane(Index + 1, Pts[Index_Of(Edge.V0())], Pts[Index_Of(Edge.V1())], theCurves[Index]);

			Try_Exception_Handle_Exit(Pts[Index_Of(Edge.V0())]->ImportEdge(Edges[Index]));
			Try_Exception_Handle_Exit(Pts[Index_Of(Edge.V1())]->ImportEdge(Edges[Index]));
		}	
	}
	MOVE(Edges);
}