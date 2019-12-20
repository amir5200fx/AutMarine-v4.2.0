#include <Cad3d_EdgeOnSolidTools.hxx>

#include <Cad3d_EdgeOnSolid.hxx>
#include <Cad3d_CurveOnPlane.hxx>
#include <Cad3d_CurveOnSurface.hxx>
#include <Cad3d_SurfaceOnSolid.hxx>
#include <Cad3d_CurveOnSurfaceTools.hxx>
#include <Geom_Pnt2d.hxx>
#include <Geom_Pnt3d.hxx>
#include <TColCad3d_HBasicQueueOfEdgeOnSolid.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace GeoLib;

#include <Geom_Curve.hxx>

Standard_Boolean AutLib::CadLib::Cad3d_EdgeOnSolidTools::CheckForConfomity
(
	const Cad3d_EdgeOnSolid & theEdge,
	const Standard_Real Tolerance
)
{
	if (NOT theEdge.CurveOnSurface()) return Standard_False;

	Debug_Null_Pointer(theEdge.CurveOnPlane());
	Debug_Null_Pointer(theEdge.CurveOnSurface());

	Geom_Pnt2d p0 = theEdge.CurveOnPlane()->FirstCoord();
	Geom_Pnt2d p1 = theEdge.CurveOnPlane()->LastCoord();

	Geom_Pnt3d P0 = theEdge.CurveOnSurface()->StartCoord();
	Geom_Pnt3d P1 = theEdge.CurveOnSurface()->LastCoord();

	if (Distance(theEdge.Surface()->Value(p0), P0) > Tolerance AND Distance(theEdge.Surface()->Value(p0), P1) > Tolerance) { return Standard_True; }
	if (Distance(theEdge.Surface()->Value(p1), P1) > Tolerance AND Distance(theEdge.Surface()->Value(p1), P0) > Tolerance) { return Standard_True; }

	return Standard_False;
}

Standard_Boolean AutLib::CadLib::Cad3d_EdgeOnSolidTools::CheckForConfomityWithDirection
(
	const Cad3d_EdgeOnSolid & theEdge, 
	const Standard_Real Tolerance
)
{
	Debug_Null_Pointer(theEdge.CurveOnPlane());
	Debug_Null_Pointer(theEdge.CurveOnSurface());

	Geom_Pnt2d p0 = theEdge.CurveOnPlane()->FirstCoord();
	Geom_Pnt2d p1 = theEdge.CurveOnPlane()->LastCoord();

	Geom_Pnt3d P0 = theEdge.CurveOnSurface()->StartCoord();
	Geom_Pnt3d P1 = theEdge.CurveOnSurface()->LastCoord();

	if (Distance(theEdge.Surface()->Value(p0), P0) > Tolerance) { return Standard_True; }
	if (Distance(theEdge.Surface()->Value(p1), P1) > Tolerance) { return Standard_True; }

	return Standard_False;
}

Standard_Boolean AutLib::CadLib::Cad3d_EdgeOnSolidTools::IsSameDirection
(
	const Cad3d_EdgeOnSolid & theEdge0,
	const Cad3d_EdgeOnSolid & theEdge1
)
{
	Debug_Null_Pointer(theEdge0.CurveOnSurface());
	Debug_Null_Pointer(theEdge1.CurveOnSurface());

	return Cad3d_CurveOnSurfaceTools::IsSameDirection(theEdge0.CurveOnSurface(), theEdge1.CurveOnSurface());
}

TColCad3d_HAry1dOfEdgeOnSolid AutLib::CadLib::Cad3d_EdgeOnSolidTools::RetrieveEdgesFrom(const TColCad3d_HAry1dOfSurfaceOnSolid & theSurfaces)
{
	TColCad3d_HBasicQueueOfEdgeOnSolid QEdges;
	forThose
	(
		Index,
		0,
		MaxIndexOf(theSurfaces)
	)
	{
		Debug_Null_Pointer(theSurfaces[Index]);

		Get_Const_Object(Edges) = theSurfaces[Index]->Edges();
		forThose(I, 0, MaxIndexOf(Edges))
		{
			/*if (Edges[I]->CurveOnSurface()->Curve())
			{
				QEdges.EnQueue(Edges[I]);
			}*/

			if (Edges[I]->CurveOnSurface())  // Debug 8/10/2018
			{
				QEdges.EnQueue(Edges[I]);
			}
		}
	}
	TColCad3d_HAry1dOfEdgeOnSolid Edges;
	QEdges.RetrieveTo(Edges);

	MOVE(Edges);
}