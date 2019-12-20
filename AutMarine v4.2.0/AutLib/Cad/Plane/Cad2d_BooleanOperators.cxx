#include <Cad2d_BooleanOperators.hxx>

#include <Standard_TypeDef.hxx>
#include <Precision.hxx>
#include <Entity_Box2d.hxx>
#include <Entity_StaticChain2d.hxx>
#include <Geom_Pnt2d.hxx>
#include <Geometry_Tools.hxx>
#include <Geometry_Distance.hxx>
#include <Cad2d_Plane.hxx>
#include <Cad2d_CurveOnPlane.hxx>
#include <Cad2d_PlanePlaneSubdivide.hxx>
#include <TColCad2d_HBasicQueueOfCurveOnPlane.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace GeoLib;

static const Standard_Integer DEFAULT_NB_OF_SEGMENTS = 20;
static const Standard_Real DEAFULT_OFFSET = EPS6;

namespace AutLib
{
	namespace CadLib
	{
		static Standard_Real CalcBetaOfChain(const Geom_Pnt2d& Point, const Geom_Pnt2d& O, const Geom_Pnt2d& P1, const Geom_Pnt2d& P2, const Standard_Real Tolerance)
		{
			//Standard_Real Epsilon = Geometry_Tools::MachineEpsilon();

			if (Geometry_Tools::Oriented(O, P1, P2) >= 0)
			{
				if (NOT Geometry_Tools::IsPointInsideOnTriangle(Point, O, P1, P2)) return 0;
				else
				{
					if (Geometry_Distance::DistanceFromLineSegment(Point, O, P1) <= Tolerance) return 0.5;

					if (Geometry_Distance::DistanceFromLineSegment(Point, O, P2) <= Tolerance) return 0.5;

					if (Geometry_Distance::DistanceFromLineSegment(Point, P1, P2) <= Tolerance) return 1.0;

					return 1.0;
				}
			}
			else
			{
				if (NOT Geometry_Tools::IsPointInsideOnTriangleCW(Point, O, P1, P2)) return 0.0;
				else
				{
					if (Geometry_Distance::DistanceFromLineSegment(Point, O, P1) <= Tolerance) return -0.5;

					if (Geometry_Distance::DistanceFromLineSegment(Point, O, P2) <= Tolerance) return -0.5;

					if (Geometry_Distance::DistanceFromLineSegment(Point, P1, P2) <= Tolerance) return 1.0;

					return -1.0;
				}
			}
		}

		static Standard_Real CalcCharFunctionOfChain(const Geom_Pnt2d& Point, const Geom_Pnt2d& O, const Entity_StaticChain2d& Chain)
		{
			Standard_Real f = 0;
			Get_Const_Object(Points) = Chain.Coords();
			Get_Const_Object(Edges) = Chain.Edges();

			const Standard_Real Tolerance = Precision::Confusion();

			forThose
			(
				Index,
				0,
				Chain.NbEdges() - 1
			)
			{
				const Standard_Integer V0 = Index_Of(Edges[Index].V0());
				const Standard_Integer V1 = Index_Of(Edges[Index].V1());

				f += CalcBetaOfChain(Point, O, Points[V0], Points[V1], Tolerance);
			}

			return f;
		}

		static Standard_Boolean IsCurveInsidePolygon(const Global_Handle(Cad2d_CurveOnPlane) Curve, const Entity_StaticChain2d& Chain, const Entity_Box2d& Domain)
		{
			Geom_Pnt2d Point = Curve->Value(MEAN(Curve->FirstParameter(), Curve->LastParameter()));

			if (NOT Geometry_Tools::IsPointInsideOnBox(Point, Domain.Xmin(), Domain.Xmax(), Domain.Ymin(), Domain.Ymax())) return Standard_False;

			Standard_Real f = CalcCharFunctionOfChain
			(
				Point,
				Domain.GetSwPoint(),
				Chain
			);

			Standard_Integer Index = Geometry_Tools::Round(f);

			if (Index EQUAL 0) return Standard_False;
			else return Standard_True;
		}
	}
}

void AutLib::CadLib::Cad2d_BooleanOperators::Union
(
	const Global_Handle(Cad2d_Plane) thePlane1,
	const Global_Handle(Cad2d_Plane) thePlane2,
	Global_Handle(Cad2d_Plane) theSum
)
{
	Debug_Null_Pointer(thePlane1);
	Debug_Null_Pointer(thePlane2);
	Debug_Null_Pointer(theSum);

	Cad2d_PlanePlaneSubdivide Intersection(thePlane1, thePlane2);

	Try_Exception_Handle_Exit(Intersection.Perform());

	Debug_If_Condition_Message(NOT Intersection.IsDone(), " Plane-Plane intersection is not performed");

	Global_Handle(Cad2d_Plane) Sub1Ptr;
	Global_Handle(Cad2d_Plane) Sub2Ptr;

	if (NOT Intersection.AreSubdivided())
	{
		Sub1Ptr = thePlane1->Copy();
		Sub2Ptr = thePlane2->Copy();
	}
	else
	{
		Sub1Ptr = Intersection.SubDivided1();
		Sub2Ptr = Intersection.SubDivided2();
	}

	Get_Const_Object(Sub1) = *Sub1Ptr;
	Get_Const_Object(Sub2) = *Sub2Ptr;

	TColCad2d_HAry1dOfCurveOnPlane Curves1, Curves2;
	Sub1.RetrieveCurvesTo(Curves1);
	Sub2.RetrieveCurvesTo(Curves2);

	Entity_StaticChain2d Chain1 = Sub1.UniDiscrete(DEFAULT_NB_OF_SEGMENTS);
	Entity_StaticChain2d Chain2 = Sub2.UniDiscrete(DEFAULT_NB_OF_SEGMENTS);

	Entity_Box2d Domain1 = Sub1.BoundingBox(DEAFULT_OFFSET);
	Entity_Box2d Domain2 = Sub2.BoundingBox(DEAFULT_OFFSET);

	TColCad2d_HBasicQueueOfCurveOnPlane Uni;

	forThose(Index, 0, MaxIndexOf(Curves1))
		if (NOT IsCurveInsidePolygon(Curves1[Index], Chain2, Domain2)) { Uni.EnQueue(Curves1[Index]->Copy()); }

	forThose(Index, 0, MaxIndexOf(Curves2))
		if (NOT IsCurveInsidePolygon(Curves2[Index], Chain1, Domain1)) { Uni.EnQueue(Curves2[Index]->Copy()); }

	Debug_If_Condition_Message(NOT Uni.Size(), " Empty Curves");

	theSum->Make(Uni.Retrive());

	FreePointer(Sub1Ptr);
	FreePointer(Sub2Ptr);
}

void AutLib::CadLib::Cad2d_BooleanOperators::Subtract
(
	const Global_Handle(Cad2d_Plane) thePlane1,
	const Global_Handle(Cad2d_Plane) thePlane2,
	Global_Handle(Cad2d_Plane) theSum
)
{
	Debug_Null_Pointer(thePlane1);
	Debug_Null_Pointer(thePlane2);
	Debug_Null_Pointer(theSum);

	Cad2d_PlanePlaneSubdivide Intersection(thePlane1, thePlane2);

	Try_Exception_Handle_Exit(Intersection.Perform());

	Debug_If_Condition_Message(NOT Intersection.IsDone(), " Plane-Plane intersection is not performed");

	Global_Handle(Cad2d_Plane) Sub1Ptr;
	Global_Handle(Cad2d_Plane) Sub2Ptr;

	if (NOT Intersection.AreSubdivided())
	{
		Sub1Ptr = thePlane1->Copy();
		Sub2Ptr = thePlane2->Copy();
	}
	else
	{
		Sub1Ptr = Intersection.SubDivided1();
		Sub2Ptr = Intersection.SubDivided2();
	}

	Get_Const_Object(Sub1) = *Sub1Ptr;
	Get_Const_Object(Sub2) = *Sub2Ptr;

	TColCad2d_HAry1dOfCurveOnPlane Curves1, Curves2;
	Sub1.RetrieveCurvesTo(Curves1);
	Sub2.RetrieveCurvesTo(Curves2);

	Entity_StaticChain2d Chain1 = Sub1.UniDiscrete(DEFAULT_NB_OF_SEGMENTS);
	Entity_StaticChain2d Chain2 = Sub2.UniDiscrete(DEFAULT_NB_OF_SEGMENTS);

	Entity_Box2d Domain1 = Sub1.BoundingBox(DEAFULT_OFFSET);
	Entity_Box2d Domain2 = Sub2.BoundingBox(DEAFULT_OFFSET);

	TColCad2d_HBasicQueueOfCurveOnPlane Uni;

	forThose(Index, 0, MaxIndexOf(Curves1))
		if (NOT IsCurveInsidePolygon(Curves1[Index], Chain2, Domain2)) 
		{ 
			Uni.EnQueue(Curves1[Index]->Copy());
		}

	forThose(Index, 0, MaxIndexOf(Curves2))
		if (IsCurveInsidePolygon(Curves2[Index], Chain1, Domain1)) 
		{ 
			Curves2[Index]->Reverse();
			Uni.EnQueue(Curves2[Index]->Copy());
		}

	Debug_If_Condition_Message(NOT Uni.Size(), " Empty Curves");
	/*Open_OutputFile_TecPlot(Plot, "test");
	TColCad2d_HAry1dOfCurveOnPlane Curves = Uni.Retrive();
	forThose(Index, 0, MaxIndexOf(Curves))
		Curves[Index]->ExportToPlt(Plot);*/
	theSum->Make(Uni.Retrive());

	FreePointer(Sub1Ptr);
	FreePointer(Sub2Ptr);
}

void AutLib::CadLib::Cad2d_BooleanOperators::Intersect
(
	const Global_Handle(Cad2d_Plane) thePlane1,
	const Global_Handle(Cad2d_Plane) thePlane2, 
	Global_Handle(Cad2d_Plane) theSum
)
{
	Debug_Null_Pointer(thePlane1);
	Debug_Null_Pointer(thePlane2);
	Debug_Null_Pointer(theSum);

	Cad2d_PlanePlaneSubdivide Intersection(thePlane1, thePlane2);

	Try_Exception_Handle_Exit(Intersection.Perform());

	Debug_If_Condition_Message(NOT Intersection.IsDone(), " Plane-Plane intersection is not performed");

	Global_Handle(Cad2d_Plane) Sub1Ptr;
	Global_Handle(Cad2d_Plane) Sub2Ptr;

	if (NOT Intersection.AreSubdivided())
	{
		Sub1Ptr = thePlane1->Copy();
		Sub2Ptr = thePlane2->Copy();
	}
	else
	{
		Sub1Ptr = Intersection.SubDivided1();
		Sub2Ptr = Intersection.SubDivided2();
	}

	Get_Const_Object(Sub1) = *Sub1Ptr;
	Get_Const_Object(Sub2) = *Sub2Ptr;

	TColCad2d_HAry1dOfCurveOnPlane Curves1, Curves2;
	Sub1.RetrieveCurvesTo(Curves1);
	Sub2.RetrieveCurvesTo(Curves2);

	Entity_StaticChain2d Chain1 = Sub1.UniDiscrete(DEFAULT_NB_OF_SEGMENTS);
	Entity_StaticChain2d Chain2 = Sub2.UniDiscrete(DEFAULT_NB_OF_SEGMENTS);

	Entity_Box2d Domain1 = Sub1.BoundingBox(DEAFULT_OFFSET);
	Entity_Box2d Domain2 = Sub2.BoundingBox(DEAFULT_OFFSET);

	TColCad2d_HBasicQueueOfCurveOnPlane Uni;

	forThose(Index, 0, MaxIndexOf(Curves1))
		if (IsCurveInsidePolygon(Curves1[Index], Chain2, Domain2)) { Uni.EnQueue(Curves1[Index]->Copy()); }

	forThose(Index, 0, MaxIndexOf(Curves2))
		if (IsCurveInsidePolygon(Curves2[Index], Chain1, Domain1)) { Uni.EnQueue(Curves2[Index]->Copy()); }

	Debug_If_Condition_Message(NOT Uni.Size(), " Empty Curves");

	theSum->Make(Uni.Retrive());

	FreePointer(Sub1Ptr);
	FreePointer(Sub2Ptr);
}