#include <Ship_Hull.hxx>

#include <Geometry_Intersect.hxx>
#include <Ship_ConstParameters.hxx>
#include <Ship_SectionControlPoints.hxx>
#include <TColGeom_Ary1dOfPnt2d.hxx>
#include <TColGeom_Ary1dOfPnt3d.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace GeoLib;

#include <BSplCLib.hxx>
#include <Geom_BSplineSurface.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <TColStd_Array1OfReal.hxx>

namespace AutLib
{
	namespace CadLib
	{

		static void Assemble
		(
			Standard_Real xSection,
			const TColGeom_Ary1dOfPnt2d& Points,
			Ship_SectionControlPoints& Section
		)
		{
			TColGeom_Ary1dOfPnt3d ControlPoints(Points.Size());

			forThose
			(
				Index,
				0,
				MaxIndexOf(ControlPoints)
			)
			{
				ControlPoints[Index].X() = xSection;
				ControlPoints[Index].Y() = Points[Index].X();
				ControlPoints[Index].Z() = Points[Index].Y();
			}

			Try_Exception_Handle_Exit(Section.SetPoints(ControlPoints););
		}

		static TColGeom_Ary1dOfPnt2d UniformDiscretLine
		(
			const Geom_Pnt2d& P0,
			const Geom_Pnt2d& P1,
			Standard_Integer NbSegments
		)
		{
			TColGeom_Ary1dOfPnt2d Points(NbSegments + 1);

			Standard_Real du = ONE / (Standard_Real)NbSegments;

			Try_Exception_Handle_Exit
			(
				forThose
				(
					Index,
					0,
					NbSegments
				)
			{
				Points[Index] = P0 + (Standard_Real)Index*du*(P1 - P0);
			}
			);

			MOVE(Points);
		}

		static void UniformSurfaceMeshParameters
		(
			Standard_Integer nI,
			Standard_Integer nJ,
			TColStd_Ary1dOfReal& uKnots,
			TColStd_Ary1dOfReal& vKnots
		)
		{
			if (uKnots.Size() != nI)
			{
				uKnots.Resize(nI);
			}

			if (vKnots.Size() != nJ)
			{
				vKnots.Resize(nJ);
			}

			if (nI < 2)
			{
				THROW_STANDARD_EXCEPTION(" Invalid Nb. of Control points in U direction");
			}

			if (nJ < 2)
			{
				THROW_STANDARD_EXCEPTION(" Invalid Nb. of Control points in V direction");
			}

			Standard_Real du = ONE / (Standard_Real)(nI - 1);
			Standard_Real dv = ONE / (Standard_Real)(nJ - 1);

			Try_Exception_Handle_Exit(uKnots[0] = ZERO);

			forThose
			(
				Index,
				1,
				nI - 2
			)
			{
				Try_Exception_Handle_Exit(uKnots[Index] = (Standard_Real)Index*du);
			}

			Try_Exception_Handle_Exit(uKnots[nI - 1] = ONE);

			Try_Exception_Handle_Exit(vKnots[0] = ZERO);

			forThose
			(
				Index,
				1,
				nJ - 2
			)
			{
				Try_Exception_Handle_Exit(vKnots[Index] = (Standard_Real)Index*dv);
			}

			Try_Exception_Handle_Exit(vKnots[nJ - 1] = ONE);
		}

		static void CalcNbControlPoints
		(
			Standard_Real Width,
			Standard_Real Height,
			Standard_Integer MaxPoints,
			Standard_Integer& NbWidth,
			Standard_Integer& NbHeight
		)
		{
			Standard_Integer Reserved = 3;

			MaxPoints -= Reserved;

			if (MaxPoints < 2)
			{
				THROW_STANDARD_EXCEPTION(" Invalid Nb. of control points");
			}

			if (Height > Width)
			{
				NbWidth = (Standard_Integer)((Width / (Width + Height))*(Standard_Real)MaxPoints);

				NbHeight = MaxPoints - NbWidth;
			}
			else
			{
				NbHeight = (Standard_Integer)((Height / (Width + Height))*(Standard_Real)MaxPoints);

				NbWidth = MaxPoints - NbHeight;
			}
		}

		static void UniformDistributionPoints
		(
			const Geom_Pnt2d& P0,
			const Geom_Pnt2d& P1,
			const Geom_Pnt2d& P2,
			Standard_Integer NbWidth,
			Standard_Integer NbHeight,
			Standard_Integer MaxPoints,
			Standard_Integer& Corner,
			TColGeom_Ary1dOfPnt2d& Points
		)
		{
			Standard_Integer
				K = 0;

			if (Points.Size() != MaxPoints)
			{
				Points.Resize(MaxPoints);
			}

			TColGeom_Ary1dOfPnt2d Inner;

			Inner = UniformDiscretLine
			(
				P0,
				P1,
				NbWidth + 1
			);

			Try_Exception_Handle_Exit
			(
				forThose
				(
					Index,
					0,
					NbWidth + 1
				)
			{
				Points[K++] = Inner[Index];
			}
			);

			Inner = UniformDiscretLine
			(
				P1,
				P2,
				NbHeight + 1
			);

			Try_Exception_Handle_Exit
			(
				forThose
				(
					Index,
					1,
					NbHeight + 1
				)
			{
				Points[K++] = Inner[Index];
			}
			);
		}

		static void SequenceKnots
		(
			const Standard_Integer Degree,
			const Standard_Integer MaxIndex,
			const TColStd_Ary1dOfReal& Parameters,
			TColStd_Ary1dOfReal& Knots
		)
		{
			Standard_Integer m = Degree + MaxIndex + 1;

			forThose
			(
				Index,
				0,
				Degree
			)
				Try_Exception_Handle_Exit(Knots[Index] = (Standard_Real)0.0);

			forThose
			(
				Index,
				m - Degree,
				m
			)
				Try_Exception_Handle_Exit(Knots[Index] = (Standard_Real)1.0);

			Standard_Real InvDegree = (Standard_Real)1.0 / (Standard_Real)Degree;

			forThose
			(
				Index,
				1,
				MaxIndex - Degree
			)
			{
				Standard_Real Sigma = (Standard_Real)0.0;

				forThose(i, Index, Index + Degree - 1)
					Sigma += Parameters[i];

				Try_Exception_Handle_Exit(Knots[Index + Degree] = InvDegree*Sigma);
			}
		}
	}
}

Global_Handle(Ship_SectionControlPoints) AutLib::CadLib::Ship_Hull::CreateRawSection
(
	const Standard_Integer Section,
	const Standard_Integer NbWidth, 
	const Standard_Integer NbHeight
)
{
	Standard_Real
		xSection,
		SideSlope,
		DeadRise,
		Width,
		Height,
		zSection;

	xSection = theXParameters_.XCoords().Value(Section);
	zSection = theXParameters_.ZCoords().Value(Section);

	SideSlope = theXParameters_.SideSlope().Value(Section);

	DeadRise = theXParameters_.DeadRise().Value(Section);

	Width = theXParameters_.YCoords().Value(Section);

	Height = theXParameters_.Depth().Value(Section) - zSection + theXParameters_.Sheer().Value(Section);

	Standard_Real MaxSideSlope = atan(Ship_ConstParameters::MaxSideSlopeCoefficient()*Width / Height);

	Standard_Real SideSlopeAngle = SideSlope*MaxSideSlope;

	theXParameters_.SideSlopeAngle().SetValue(Section, SideSlopeAngle);

	Geom_Pnt2d P0(0, zSection);
	Geom_Pnt2d P2(Width, zSection + Height);
	
	Standard_Real MaxDeadRiseHeight = Ship_ConstParameters::MaxDeadRiseCoefficient()*Height;
	Standard_Real MaxDeadRiseAngle = atan(MaxDeadRiseHeight / Width);

	Geom_Pnt2d t0(cos(DeadRise*MaxDeadRiseAngle), sin(DeadRise*MaxDeadRiseAngle));
	Geom_Pnt2d t2(-sin(SideSlopeAngle), -cos(SideSlopeAngle));

	Geom_Pnt2d IP;

	Try_Exception_Handle_Exit
	(
		IP = Geometry_Intersect::IntersectionTwoLines
		(
			P0,
			t0,
			P2,
			t2
		);
	);

	TColGeom_Ary1dOfPnt2d Points;

	Standard_Integer MaxPoints = theParameters_.Dimensions().NbNetRows();
	Standard_Integer Corner = NbWidth + 1;

	UniformDistributionPoints
	(
		P0,
		IP,
		P2,
		NbWidth,
		NbHeight,
		MaxPoints,
		Corner,
		Points
	);

	Global_Handle(Ship_SectionControlPoints) NewSectionPtr = new Ship_SectionControlPoints(Points.Size());

	Assemble
	(
		xSection,
		Points,
		*NewSectionPtr
	);

	Try_Exception_Handle_Exit((*NewSectionPtr).SetCorner(Corner););

	return NewSectionPtr;
}

Global_Handle(Ship_SectionControlPoints) AutLib::CadLib::Ship_Hull::CreateRawStem()
{
	Standard_Integer Section = theParameters_.Dimensions().NbNetColumns() - 1;

	Standard_Real xSection = theXParameters_.XCoords().Value(Section);
	Standard_Real Width = (Standard_Real)0.0;
	Standard_Real Height = theParameters_.Dimensions().DepthAtBow();

	Geom_Pnt2d P0;
	Geom_Pnt2d P1((Standard_Real)0.0, Height);

	Standard_Integer MaxPoints = theParameters_.Dimensions().NbNetRows() - 1;

	TColGeom_Ary1dOfPnt2d Points = UniformDiscretLine
	(
		P0,
		P1,
		MaxPoints - 1
	);
	
	Global_Handle(Ship_SectionControlPoints) NewSectionPtr = new Ship_SectionControlPoints(Points.Size());

	Assemble
	(
		xSection,
		Points,
		*NewSectionPtr
	);

	Try_Exception_Handle_Exit((*NewSectionPtr).SetCorner(0));

	return NewSectionPtr;
}

Global_Handle(Ship_SectionControlPoints) AutLib::CadLib::Ship_Hull::CreateRawStemPaired()
{
	Standard_Integer Section = theParameters_.Dimensions().NbNetColumns() - 2;

	Standard_Real xSection = theXParameters_.XCoords().Value(Section);
	Standard_Real ySection = theXParameters_.YCoords().Value(Section);
	Standard_Real xSideSlope = theXParameters_.SideSlope().Value(Section);
	Standard_Real Height = theParameters_.Dimensions().DepthAtBow();

	Standard_Real MaxSideSlope = atan(Ship_ConstParameters::MaxSideSlopeCoefficient()*ySection / Height);

	Standard_Real SideSlopeAngle = xSideSlope*MaxSideSlope;

	theXParameters_.SideSlopeAngle().SetValue(Section, SideSlopeAngle);

	Standard_Real dy = tan(SideSlopeAngle)*Height;

	Standard_Real y0 = MIN(ySection, ySection - dy);

	y0 = MAX(y0, ySection*Ship_ConstParameters::MinDistanceCoefficient());

	Geom_Pnt2d P0(y0, (Standard_Real)0.0);
	Geom_Pnt2d P1(ySection, Height);

	Standard_Integer MaxPoints = theParameters_.Dimensions().NbNetRows() - 1;

	TColGeom_Ary1dOfPnt2d Points = UniformDiscretLine(P0, P1, MaxPoints - 1);

	Global_Handle(Ship_SectionControlPoints) NewSectionPtr = new Ship_SectionControlPoints(Points.Size());

	Assemble
	(
		xSection,
		Points,
		*NewSectionPtr
	);

	Try_Exception_Handle_Exit((*NewSectionPtr).SetCorner(1));

	return NewSectionPtr;
}

void AutLib::CadLib::Ship_Hull::CreateRawSections()
{
	const Ship_Dimensions & Dimensions = theParameters_.Dimensions();

	Standard_Integer NbSections = Dimensions.NbNetColumns();
	Standard_Integer
		NbWidth,
		NbHeight;

	Try_Exception_Handle_Exit
	(
		CalcNbControlPoints
		(
			Dimensions.BeamOnDeck(),
			MEAN(Dimensions.DepthAtBow(), Dimensions.DepthAtTransom()),
			Dimensions.NbNetRows(),
			NbWidth,
			NbHeight
		);
	);

	if (NbHeight < 0 || NbWidth < 0)
	{
		THROW_STANDARD_EXCEPTION(" Invalid Nb. of Inner control points");
	}

	forThose
	(
		Section,
		0,
		NbSections - 3
	)
	{
		SetSection
		(
			Section,
			CreateRawSection(Section, NbWidth, NbHeight)
		);
	}

	SetSection(NbSections - 2, CreateRawStemPaired());
	SetSection(NbSections - 1, CreateRawStem());
}

void AutLib::CadLib::Ship_Hull::SetupControlNet()
{
	const Ship_Dimensions & Dimension = theParameters_.Dimensions();

	Standard_Integer
		NbSections,
		NbRows,
		I = 0;

	NbSections = Dimension.NbNetColumns();
	NbRows = Dimension.NbNetRows();

	Geom_Pnt3d Point;

	Global_Handle(Ship_SectionControlPoints) SectionPtr(0);

	forThose
	(
		Section,
		0,
		NbSections - 1
	)
	{
		if (Section + 1 > NbSections - 2) I = 1;

		Try_Exception_Handle_Exit(SectionPtr = theSections_[Section]);

		if (SectionPtr == NULL)
		{
			THROW_STANDARD_EXCEPTION(" Null Section Pointer");
		}

		const TColGeom_Ary1dOfPnt3d & ControlPoints = SectionPtr->ControlPoints();

		forThose
		(
			J,
			0,
			(NbRows - I) - 1
		)
		{
			Try_Exception_Handle_Exit(Point = ControlPoints[J]);

			SetControlPoint
			(
				Section,
				J + I,
				Point
			);
		}
	}

	Point = theControlNet_->Value(NbSections, 2);

	SetControlPoint(NbSections - 1, 0, Point);

	SetControlPoint(NbSections - 2, 0, Point);
}

void AutLib::CadLib::Ship_Hull::SetupPatch()
{
	TColStd_Ary1dOfReal
		uParameters,
		vParameters;

	Standard_Integer
		uDegree,
		vDegree,
		uMaxIndex,
		vMaxIndex;

	const Ship_Dimensions & Dimension = theParameters_.Dimensions();

	Standard_Integer NbSections = Dimension.NbNetColumns();
	Standard_Integer NbRows = Dimension.NbNetRows();

	UniformSurfaceMeshParameters
	(
		NbSections,
		NbRows,
		uParameters,
		vParameters
	);

	uDegree = vDegree = 3;

	uMaxIndex = NbSections - 1;
	vMaxIndex = NbRows - 1;

	TColStd_Ary1dOfReal
		uKnots(uMaxIndex + uDegree + 2),
		vKnots(vMaxIndex + vDegree + 2);

	SequenceKnots
	(
		uDegree,
		uMaxIndex,
		uParameters,
		uKnots
	);

	SequenceKnots
	(
		vDegree,
		vMaxIndex,
		vParameters,
		vKnots
	);

	TColStd_Array1OfReal Seq_uKnots(1, uKnots.Size());
	TColStd_Array1OfReal Seq_vKnots(1, vKnots.Size());

	forThose(Index, 0, MaxIndexOf(uKnots))
		Seq_uKnots.SetValue(Index + 1, uKnots[Index]);

	forThose(Index, 0, MaxIndexOf(vKnots))
		Seq_vKnots.SetValue(Index + 1, vKnots[Index]);

	Standard_Integer uLength = BSplCLib::KnotsLength(Seq_uKnots);
	Standard_Integer vLength = BSplCLib::KnotsLength(Seq_vKnots);

	TColStd_Array1OfReal uKnotVector(1, uLength);
	TColStd_Array1OfReal vKnotVector(1, vLength);
	TColStd_Array1OfInteger uMult(1, uLength);
	TColStd_Array1OfInteger vMult(1, vLength);

	BSplCLib::Knots(Seq_uKnots, uKnotVector, uMult);
	BSplCLib::Knots(Seq_vKnots, vKnotVector, vMult);

	theHull_ = new Geom_BSplineSurface(*theControlNet_, uKnotVector, vKnotVector, uMult, vMult, uDegree, vDegree);
}