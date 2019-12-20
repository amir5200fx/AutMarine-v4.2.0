#include <Mesh3d_EdgeRemovalEquatorialTrianglesTools.hxx>

#include <Mesh3d_Edge.hxx>
#include <Mesh3d_EdgeTools.hxx>
#include <Mesh3d_EdgeRemovalEquatorialTriangles.hxx>
#include <Mesh3d_EdgeRemovalEquatorialTrianglesThreeNodes.hxx>
#include <Mesh3d_EdgeRemovalEquatorialTrianglesFourNodes.hxx>
#include <Mesh3d_EdgeRemovalEquatorialTrianglesFiveNodes.hxx>
#include <Mesh3d_EdgeRemovalEquatorialTrianglesSixNodes.hxx>
#include <Mesh3d_EdgeRemovalEquatorialTrianglesSevenNodes.hxx>
#include <Mesh3d_EdgeRemovalEquatorialTrianglesFourNodesTools.hxx>
#include <Mesh3d_EdgeRemovalEquatorialTrianglesFiveNodesTools.hxx>
#include <Mesh3d_QualityMap.hxx>
#include <TColMesh3d_HAry1dOfElement.hxx>
#include <TColGeom_Ary1dOfPnt3d.hxx>

using namespace AutLib;
using namespace MeshLib;
using namespace GeoLib;

static const TColEntity_Ary1dOfTriangleIndex EquatorialTrianglesFourNodes1 = Mesh3d_EdgeRemovalEquatorialTrianglesFourNodesTools::EquatorialTrianglesArrange1();
static const TColEntity_Ary1dOfTriangleIndex EquatorialTrianglesFourNodes2 = Mesh3d_EdgeRemovalEquatorialTrianglesFourNodesTools::EquatorialTrianglesArrange2();

static const TColEntity_Ary1dOfTriangleIndex EquatorialTrianglesFiveNodes1 = Mesh3d_EdgeRemovalEquatorialTrianglesFiveNodesTools::EquatorialTrianglesArrange(0);
static const TColEntity_Ary1dOfTriangleIndex EquatorialTrianglesFiveNodes2 = Mesh3d_EdgeRemovalEquatorialTrianglesFiveNodesTools::EquatorialTrianglesArrange(1);
static const TColEntity_Ary1dOfTriangleIndex EquatorialTrianglesFiveNodes3 = Mesh3d_EdgeRemovalEquatorialTrianglesFiveNodesTools::EquatorialTrianglesArrange(2);
static const TColEntity_Ary1dOfTriangleIndex EquatorialTrianglesFiveNodes4 = Mesh3d_EdgeRemovalEquatorialTrianglesFiveNodesTools::EquatorialTrianglesArrange(3);
static const TColEntity_Ary1dOfTriangleIndex EquatorialTrianglesFiveNodes5 = Mesh3d_EdgeRemovalEquatorialTrianglesFiveNodesTools::EquatorialTrianglesArrange(4);

namespace AutLib
{
	namespace MeshLib
	{

		static TColGeom_Ary1dOfPnt3d GetCoords(const TColMesh3d_HAry1dOfNode& theRing)
		{
			TColGeom_Ary1dOfPnt3d Coords(theRing.Size());
			forThose
			(
				Index, 
				0, 
				MaxIndexOf(theRing)
			)
			{
				Debug_Null_Pointer(theRing[Index]);
				Coords[Index] = theRing[Index]->Coord();
			}
			MOVE(Coords);
		}

		static inline Standard_Boolean ReveseRing(const Geom_Pnt3d& theP0, const Geom_Pnt3d& theP1, const TColGeom_Ary1dOfPnt3d& theCoords)
		{
			Geom_Pnt3d Tang = (theP1 - theP0).UnitLength();
			Get_Const_Object(P0) = theCoords[0];
			Get_Const_Object(P1) = theCoords[1];

			Geom_Pnt3d V0 = P0 - theP0;
			Geom_Pnt3d V1 = P1 - theP0;

			return DotProduct(Tang, CrossProduct(V0, V1).UnitLength()) < 0;
		}

		static Standard_Boolean ReveseRing(const Mesh3d_Edge & theEdge, const TColMesh3d_HAry1dOfNode& theRing)
		{
			Debug_Null_Pointer(theEdge.Node1());

			Get_Const_Object(Pr) = theEdge.Node1()->Coord();

			Geom_Pnt3d Pm = theEdge.Centre();
			TColGeom_Ary1dOfPnt3d Coords = GetCoords(theRing);

			return ::ReveseRing(Pm, Pr, Coords);
		}

		static inline Standard_Real CalcWorstQuality(const Mesh3d_Edge & theEdge, const TColMesh3d_HAry1dOfNode& theRing, const Mesh3d_QualityMap& theQualityMap, const TColEntity_Ary1dOfTriangleIndex& theTriangulation)
		{
			Debug_Null_Pointer(theEdge.Node0());
			Debug_Null_Pointer(theEdge.Node1());

			Get_Const_Object(Pf) = theEdge.Node0()->Coord();
			Get_Const_Object(Pl) = theEdge.Node1()->Coord();

			Standard_Real WorstQuality = RealLast();
			forThose
			(
				Index,
				0, 
				MaxIndexOf(theTriangulation)
			)
			{
				Get_Const_Object(Triangle) = theTriangulation[Index];

				Get_Const_Object(P0) = theRing[Index_Of(Triangle.V0())]->Coord();
				Get_Const_Object(P1) = theRing[Index_Of(Triangle.V1())]->Coord();
				Get_Const_Object(P2) = theRing[Index_Of(Triangle.V2())]->Coord();

				Standard_Real Quality1 = theQualityMap.CalcQuality(P0, P1, P2, Pl);
				if (Quality1 < WorstQuality) WorstQuality = Quality1;

				Standard_Real Quality2 = theQualityMap.CalcQuality(P2, P1, P0, Pf);
				if (Quality2 < WorstQuality) WorstQuality = Quality2;
			}
			return WorstQuality;
		}

		static Standard_Real BestQualityFiveNodes(const Mesh3d_Edge & theEdge, const TColMesh3d_HAry1dOfNode& theRing, const Mesh3d_QualityMap& theQualityMap, TColEntity_Ary1dOfTriangleIndex& theTriangulation)
		{
			Debug_If_Condition(theRing.Size() NOT_EQUAL 5);

			Standard_Real Worst1 = CalcWorstQuality(theEdge, theRing, theQualityMap, EquatorialTrianglesFiveNodes1);
			Standard_Real Worst2 = CalcWorstQuality(theEdge, theRing, theQualityMap, EquatorialTrianglesFiveNodes2);
			Standard_Real Worst3 = CalcWorstQuality(theEdge, theRing, theQualityMap, EquatorialTrianglesFiveNodes3);
			Standard_Real Worst4 = CalcWorstQuality(theEdge, theRing, theQualityMap, EquatorialTrianglesFiveNodes4);
			Standard_Real Worst5 = CalcWorstQuality(theEdge, theRing, theQualityMap, EquatorialTrianglesFiveNodes5);

			Standard_Real Worst = -1;
			Standard_Integer K = 0;
			if (Worst1 > Worst)
			{
				Worst = Worst1;
				K = 1;
			}

			if (Worst2 > Worst)
			{
				Worst = Worst2;
				K = 2;
			}

			if (Worst3 > Worst)
			{
				Worst = Worst3;
				K = 3;
			}

			if (Worst4 > Worst)
			{
				Worst = Worst4;
				K = 4;
			}

			if (Worst5 > Worst)
			{
				Worst = Worst5;
				K = 5;
			}

			switch (K)
			{
			case 1:
				theTriangulation = EquatorialTrianglesFiveNodes1;
				return Worst;
			case 2:
				theTriangulation = EquatorialTrianglesFiveNodes2;
				return Worst;
			case 3:
				theTriangulation = EquatorialTrianglesFiveNodes3;
				return Worst;
			case 4:
				theTriangulation = EquatorialTrianglesFiveNodes4;
				return Worst;
			case 5:
				theTriangulation = EquatorialTrianglesFiveNodes5;
				return Worst;
			default:
				return 0;
			}
			return 0;
		}

		static Standard_Real BestQualityFourNodes(const Mesh3d_Edge & theEdge, const TColMesh3d_HAry1dOfNode& theRing, const Mesh3d_QualityMap& theQualityMap, TColEntity_Ary1dOfTriangleIndex& theTriangulation)
		{
			Debug_If_Condition(theRing.Size() NOT_EQUAL 4);

			Standard_Real Worst1 = CalcWorstQuality(theEdge, theRing, theQualityMap, EquatorialTrianglesFourNodes1);
			Standard_Real Worst2 = CalcWorstQuality(theEdge, theRing, theQualityMap, EquatorialTrianglesFourNodes2);

			if (Worst1 > Worst2)
			{
				theTriangulation = EquatorialTrianglesFourNodes1;
				return Worst1;
			}
			else
			{
				theTriangulation = EquatorialTrianglesFourNodes2;
				return Worst2;
			}		
		}

		static Standard_Real BestQualityThreeNodes(const Mesh3d_Edge & theEdge, const TColMesh3d_HAry1dOfNode& theRing, const Mesh3d_QualityMap& theQualityMap, TColEntity_Ary1dOfTriangleIndex& theTriangulation)
		{
			Debug_If_Condition(theRing.Size() NOT_EQUAL 3);

			Debug_Null_Pointer(theEdge.Node0());
			Debug_Null_Pointer(theEdge.Node1());

			Get_Const_Object(Pl) = theEdge.Node0()->Coord();
			Get_Const_Object(Pr) = theEdge.Node1()->Coord();

			TColGeom_Ary1dOfPnt3d Coords = GetCoords(theRing);

			theTriangulation.Resize(1);
			theTriangulation[0].SetValue(1, 2, 3);

			return MIN(theQualityMap.CalcQuality(Coords[0], Coords[1], Coords[2], Pr), theQualityMap.CalcQuality(Coords[2], Coords[1], Coords[0], Pl));
		}

		static Standard_Boolean BestTriangulation(const Mesh3d_Edge & theEdge, const TColMesh3d_HAry1dOfNode& theRing, const Mesh3d_QualityMap& theQualityMap, TColEntity_Ary1dOfTriangleIndex& theTriangulation, Standard_Real& theWorstQuality)
		{
			if (theRing.Size() EQUAL 3)
			{
				theWorstQuality = BestQualityThreeNodes(theEdge, theRing, theQualityMap, theTriangulation);
				if (theWorstQuality <= 0) { return Standard_False; }
				return Standard_True;
			}

			if (theRing.Size() EQUAL 4)
			{
				theWorstQuality = BestQualityFourNodes(theEdge, theRing, theQualityMap, theTriangulation);
				if (theWorstQuality <= 0) { return Standard_False; }
				return Standard_True;
			}

			if (theRing.Size() EQUAL 5)
			{
				theWorstQuality = BestQualityFiveNodes(theEdge, theRing, theQualityMap, theTriangulation);
				if (theWorstQuality <= 0) { return Standard_False; }
				return Standard_True;
			}

			return Standard_False;
		}
	}
}

Global_Handle(Mesh3d_EdgeRemovalEquatorialTriangles) AutLib::MeshLib::Mesh3d_EdgeRemovalEquatorialTrianglesTools::CreateEquatorialTriangle
(
	const Mesh3d_Edge & theEdge, 
	const Mesh3d_QualityMap& theQualityMap
)
{
	TColMesh3d_HAry1dOfElement Elements;
	theEdge.RetrieveTo(Elements);

	if (Elements.Size() < 2) { THROW_STANDARD_EXCEPTION("Invalid to EdgeRemoval"); }

	//if (Elements.Size() > 2) { THROW_STANDARD_EXCEPTION("The nb. of elements > 2 not implemented yet!"); }

	TColMesh3d_HAry1dOfEdge RingEdges;
	TColMesh3d_HAry1dOfNode Ring = Mesh3d_EdgeTools::RetrieveStarNodesAround(theEdge, RingEdges);
	if (::ReveseRing(theEdge, Ring))
	{
		Ring.Reverse();
		RingEdges.Reverse();
	}

	Standard_Real WorstQuality;
	TColEntity_Ary1dOfTriangleIndex Triangulation;
	Global_Handle(Mesh3d_EdgeRemovalEquatorialTriangles) EquatorialTriangles(0);
	if (BestTriangulation(theEdge, Ring, theQualityMap, Triangulation, WorstQuality))
	{
		switch (Ring.Size())
		{
		case 3:
			EquatorialTriangles = new Mesh3d_EdgeRemovalEquatorialTrianglesThreeNodes(Ring, RingEdges, Triangulation);
			EquatorialTriangles->SetWorstQuality(WorstQuality);
			break;
		case 4:
			EquatorialTriangles = new Mesh3d_EdgeRemovalEquatorialTrianglesFourNodes(Ring, RingEdges, Triangulation);
			EquatorialTriangles->SetWorstQuality(WorstQuality);
			break;
		case 5:
			EquatorialTriangles = new Mesh3d_EdgeRemovalEquatorialTrianglesFiveNodes(Ring, RingEdges, Triangulation);
			EquatorialTriangles->SetWorstQuality(WorstQuality);
			break;
		case 6:
			/*EquatorialTriangles = new Mesh3d_EdgeRemovalEquatorialTrianglesSixNodes(Ring, RingEdges, Triangulation);
			EquatorialTriangles->SetWorstQuality(WorstQuality);*/
			break;
		case 7:
			/*EquatorialTriangles = new Mesh3d_EdgeRemovalEquatorialTrianglesSevenNodes(Ring, RingEdges, Triangulation);
			EquatorialTriangles->SetWorstQuality(WorstQuality);*/
			break;
		default:
			break;
		}
		
	}

	return EquatorialTriangles;
}