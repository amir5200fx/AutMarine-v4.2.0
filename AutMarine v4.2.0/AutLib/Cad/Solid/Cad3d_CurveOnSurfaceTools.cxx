#include <Cad3d_CurveOnSurfaceTools.hxx>

#include <Entity_PolyLine3d.hxx>
#include <Geometry_Distance.hxx>
#include <Geometry_Sort.hxx>
#include <Cad3d_CurveOnSurface.hxx>
#include <Cad3d_EdgeOnSolid.hxx>
#include <Cad3d_SurfaceOnSolid.hxx>
#include <Cad3d_RingOnSurface.hxx>
#include <TColStd_Ary1dOfReal.hxx>
#include <TColGeom_Ary1dOfPnt3d.hxx>
#include <TColStd_BasicQueueOfReal.hxx>
#include <TColCad3d_HBasicQueueOfEdgeOnSolid.hxx>

#include <Geom_Curve.hxx>
#include <GeomAPI_ProjectPointOnCurve.hxx>
#include <GeomAPI_ExtremaCurveCurve.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace GeoLib;

namespace AutLib
{
	namespace CadLib
	{

		static inline TColStd_Ary1dOfReal CalcNormalizedSamplingParameters(const Standard_Integer NbSmapling)
		{
			THROW_STANDARD_EXCEPTION_IF(NbSmapling < 1, "Invalid sampling number");

			Standard_Real Dt = 1.0 / (Standard_Real)(NbSmapling + 1);
			TColStd_Ary1dOfReal Sampling(NbSmapling);

			forThose(Index, 1, NbSmapling)
				Sampling[Index_Of(Index)] = Dt*Index;

			MOVE(Sampling);
		}

		static inline void CalcSamples(const TColStd_Ary1dOfReal& Normalized, const Standard_Real U0, const Standard_Real U1, TColStd_Ary1dOfReal& Params)
		{
			Params.Resize(Normalized.Size());

			Standard_Real Dt = U1 - U0;
			forThose(Index, 0, MaxIndexOf(Normalized))
			{
				Params[Index] = U0 + Dt*Normalized[Index];
			}
		}

		static Standard_Boolean doSubdivide(const Standard_Real U0, const Standard_Real U1, const TColStd_Ary1dOfReal& Normalized, const Cad3d_CurveOnSurface& theEdge, const Standard_Real Proximity, Standard_Real& tm)
		{
			TColStd_Ary1dOfReal Params;
			CalcSamples(Normalized, U0, U1, Params);

			const Handle(Geom_Curve)& Curve = theEdge.Curve();

			TColGeom_Ary1dOfPnt3d Samples(Params.Size());
			forThose(Index, 0, MaxIndexOf(Samples))
				Samples[Index] = Curve->Value(Params[Index]);

			Geom_Pnt3d P0 = Curve->Value(U0);
			Geom_Pnt3d P1 = Curve->Value(U1);

			Standard_Real MaxDistance = 0;
			forThose
			(
				Index,
				0,
				MaxIndexOf(Samples)
			)
			{
				Standard_Real Dist = Geometry_Distance::DistanceFromLineSegment(Samples[Index], P0, P1);
				if (Dist > MaxDistance)
				{
					MaxDistance = Dist;
					tm = Params[Index];
				}
			}

			if (MaxDistance > Proximity) { return Standard_True; }
			return Standard_False;
		}

		static void Discrete(const Standard_Real U0, const Standard_Real U1, const TColStd_Ary1dOfReal& Normalized, const Cad3d_CurveOnSurface& theEdge, const Standard_Real Proximity, TColStd_BasicQueueOfReal& QParams)
		{
			Standard_Real tm;
			if (doSubdivide(U0, U1, Normalized, theEdge, Proximity, tm))
			{
				QParams.EnQueue(tm);

				Discrete(U0, tm, Normalized, theEdge, Proximity, QParams);
				Discrete(tm, U1, Normalized, theEdge, Proximity, QParams);
			}
		}

		static void MakePolyLine(const TColStd_Ary1dOfReal& Params, const Cad3d_CurveOnSurface& theEdge, const Standard_Real Proximity, Entity_PolyLine3d& Poly)
		{
			Get_Object(Pts) = Poly.Points();
			Pts.Resize(Params.Size());

			const Handle(Geom_Curve)& Curve = theEdge.Curve();

			forThose(Index, 0, MaxIndexOf(Pts))
				Pts[Index] = Curve->Value(Params[Index]);

			Poly.SetDeflection(Proximity);
		}
	}
}

Entity_PolyLine3d AutLib::CadLib::Cad3d_CurveOnSurfaceTools::DiscretizedOf
(
	const Cad3d_CurveOnSurface & EdgeOnSurface,
	const Standard_Real Deflection,
	const Standard_Real Tolerance,
	const Standard_Integer NbSamples
)
{
	Standard_Real U0 = EdgeOnSurface.FirstParameter();
	Standard_Real U1 = EdgeOnSurface.LastParameter();

	TColStd_BasicQueueOfReal QParams;
	QParams.EnQueue(U0);

	TColStd_Ary1dOfReal Normalized = CalcNormalizedSamplingParameters(NbSamples);

	if (EdgeOnSurface.IsClosed(Tolerance))
	{
		Standard_Real tm = MEAN(U0, U1);

		Discrete(U0, tm, Normalized, EdgeOnSurface, Deflection, QParams);

		QParams.EnQueue(tm);

		Discrete(tm, U1, Normalized, EdgeOnSurface, Deflection, QParams);
	}
	else
	{
		Discrete(U0, U1, Normalized, EdgeOnSurface, Deflection, QParams);
	}

	QParams.EnQueue(U1);

	TColStd_Ary1dOfReal Params;
	QParams.RetrieveTo(Params);

	Geometry_Sort<Standard_Real>::Sort(Params);

	Entity_PolyLine3d PolyLine;
	MakePolyLine(Params, EdgeOnSurface, Deflection, PolyLine);

	MOVE(PolyLine);
}

Standard_Boolean AutLib::CadLib::Cad3d_CurveOnSurfaceTools::IsSameDirection
(
	const Global_Handle(Cad3d_CurveOnSurface) theCurve1,
	const Global_Handle(Cad3d_CurveOnSurface) theCurve2
)
{
	Global_Handle(Cad3d_RingOnSurface) Ring1 = Global_DownCast(Cad3d_RingOnSurface, (Global_Handle(Cad3d_CurveOnSurface))theCurve1);
	Global_Handle(Cad3d_RingOnSurface) Ring2 = Global_DownCast(Cad3d_RingOnSurface, (Global_Handle(Cad3d_CurveOnSurface))theCurve2);

	if (Ring1 AND Ring2)
	{
		return Ring1->IsSameDirection(*Ring2);
	}

	if (Ring1) return Standard_False;
	if (Ring2) return Standard_False;

	return theCurve1->IsSameDirection(*theCurve2);
}

Standard_Real AutLib::CadLib::Cad3d_CurveOnSurfaceTools::Distance
(
	const Geom_Pnt3d & thePoint, 
	const Cad3d_CurveOnSurface & theEdge
)
{
	Debug_Null_Pointer(theEdge.Curve());

	GeomAPI_ProjectPointOnCurve Projection;
	Projection.Init(theEdge.Curve(), theEdge.FirstParameter(), theEdge.LastParameter());
	Projection.Perform(thePoint);

	return Projection.LowerDistance();
}

Standard_Real AutLib::CadLib::Cad3d_CurveOnSurfaceTools::Distance
(
	const Cad3d_CurveOnSurface & theEdge1,
	const Cad3d_CurveOnSurface & theEdge2
)
{
	Debug_Null_Pointer(theEdge1.Curve());
	Debug_Null_Pointer(theEdge2.Curve());

	GeomAPI_ExtremaCurveCurve Extrema;
	Extrema.Init
	(
		theEdge1.Curve(),
		theEdge2.Curve(), 
		theEdge1.FirstParameter(),
		theEdge1.LastParameter(),
		theEdge2.FirstParameter(),
		theEdge2.LastParameter()
	);
	
	return Extrema.LowerDistance();
}
