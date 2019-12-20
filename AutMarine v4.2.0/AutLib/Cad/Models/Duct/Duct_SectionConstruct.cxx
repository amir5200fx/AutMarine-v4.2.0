#include <Duct_Hull.hxx>

#include <Geom_Pnt2d.hxx>
#include <Duct_SectionControlPoints.hxx>
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
			Duct_SectionControlPoints& Section
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
			TColStd_Ary1dOfReal& uKnots
		)
		{
			if (uKnots.Size() != nI)
			{
				uKnots.Resize(nI);
			}

			if (nI < 2)
			{
				THROW_STANDARD_EXCEPTION(" Invalid Nb. of Control points in U direction");
			}

			Standard_Real du = ONE / (Standard_Real)(nI - 1);

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

Global_Handle(Duct_SectionControlPoints) AutLib::CadLib::Duct_Hull::CreateSection(const Standard_Integer Section) const
{
	Standard_Real
		xSection,
		SideSlope,
		Width,
		Breadth,
		Depth,
		UpperTightness,
		LowerTightness,
		zSection;

	xSection = theXParameters_.XCoords().Value(Section);
	zSection = theXParameters_.ZCoords().Value(Section);

	SideSlope = theXParameters_.SideSlope().Value(Section);

	Width = theXParameters_.Width().Value(Section);
	Breadth = theXParameters_.YCoords().Value(Section) / 2;
	Depth = theXParameters_.Depth().Value(Section);

	Geom_Pnt2d P0(0, zSection);
	Geom_Pnt2d P5(Breadth, zSection + 0.5*Depth);
	Geom_Pnt2d P10(0, zSection + Depth);

	Standard_Real t0 = -1 + SideSlope * 2;
	Geom_Pnt2d P3(P5.X() + t0*P5.X(), zSection);
	Geom_Pnt2d P7(P5.X() - t0*P5.X(), P10.Y());

	LowerTightness = theXParameters_.LowerTightness().Value(Section);
	UpperTightness = theXParameters_.UpperTightness().Value(Section);

	Geom_Pnt2d P2(P3.X() + LowerTightness*(P0.X() - P3.X()), P3.Y());
	Geom_Pnt2d P8(P7.X() + UpperTightness*(P10.X() - P7.X()), P7.Y());

	Geom_Pnt2d P1 = MEAN(P2, P0);
	Geom_Pnt2d P9 = MEAN(P8, P10);
	
	Geom_Pnt2d P4 = P3 + LowerTightness*(P5 - P3);
	Geom_Pnt2d P6 = P7 + UpperTightness*(P5 - P7);

	Global_Handle(Duct_SectionControlPoints) newSection = new Duct_SectionControlPoints;
	Get_Object(Coords) = newSection->ControlPoints();

	Coords.SetValue(0, Geom_Pnt3d(xSection, P0.X(), P0.Y()));
	Coords.SetValue(1, Geom_Pnt3d(xSection, P1.X(), P1.Y()));
	Coords.SetValue(2, Geom_Pnt3d(xSection, P2.X(), P2.Y()));
	Coords.SetValue(3, Geom_Pnt3d(xSection, P3.X(), P3.Y()));
	Coords.SetValue(4, Geom_Pnt3d(xSection, P4.X(), P4.Y()));
	Coords.SetValue(5, Geom_Pnt3d(xSection, P5.X(), P5.Y()));
	Coords.SetValue(6, Geom_Pnt3d(xSection, P6.X(), P6.Y()));
	Coords.SetValue(7, Geom_Pnt3d(xSection, P7.X(), P7.Y()));
	Coords.SetValue(8, Geom_Pnt3d(xSection, P8.X(), P8.Y()));
	Coords.SetValue(9, Geom_Pnt3d(xSection, P9.X(), P9.Y()));
	Coords.SetValue(10, Geom_Pnt3d(xSection, P10.X(), P10.Y()));

	return newSection;
}

void AutLib::CadLib::Duct_Hull::CreateSections()
{
	const Duct_Dimensions & Dimensions = theParameters_.Dimensions();

	Standard_Integer NbSections = Dimensions.NbSections();

	forThose(Section, 0, NbSections - 1)
	{
		theSections_[Section] = CreateSection(Section);
	}
}

void AutLib::CadLib::Duct_Hull::SetupControlNet()
{
	const Duct_Dimensions & Dimension = theParameters_.Dimensions();

	Standard_Integer
		NbSections,
		NbRows,
		I = 0;

	NbSections = Dimension.NbSections();
	NbRows = 11;

	Geom_Pnt3d Point;

	Global_Handle(Duct_SectionControlPoints) SectionPtr(0);

	theWeightNet_->Init(1.0);

	forThose
	(
		Section,
		0,
		NbSections - 1
	)
	{
		Try_Exception_Handle_Exit(SectionPtr = theSections_[Section]);

		if (SectionPtr == NULL)
		{
			THROW_STANDARD_EXCEPTION(" Null Section Pointer");
		}

		const TColGeom_Ary1dOfPnt3d & ControlPoints = SectionPtr->ControlPoints();

		forThose(J, 0, MaxIndexOf(ControlPoints))
		{
			Try_Exception_Handle_Exit(Point = ControlPoints[J]);

			theControlNet_->SetValue(Section + 1, J + 1, Point);
		}

		theWeightNet_->SetValue(Section + 1, 4, 0.7071068);
		theWeightNet_->SetValue(Section + 1, 8, 0.7071068);
	}
}

void AutLib::CadLib::Duct_Hull::SetupPatch()
{
	TColStd_Ary1dOfReal
		uParameters;

	Standard_Integer
		uDegree,
		vDegree,
		uMaxIndex,
		vMaxIndex;

	const Duct_Dimensions & Dimension = theParameters_.Dimensions();

	Standard_Integer NbSections = Dimension.NbSections();
	Standard_Integer NbRows = 11;

	UniformSurfaceMeshParameters
	(
		NbSections,
		uParameters
	);

	uDegree = 3;
	vDegree = 2;

	uMaxIndex = NbSections - 1;
	vMaxIndex = NbRows - 1;

	TColStd_Ary1dOfReal
		uKnots(uMaxIndex + uDegree + 2);

	SequenceKnots
	(
		uDegree,
		uMaxIndex,
		uParameters,
		uKnots
	);

	TColStd_Array1OfReal Seq_uKnots(1, uKnots.Size());

	forThose(Index, 0, MaxIndexOf(uKnots))
		Seq_uKnots.SetValue(Index + 1, uKnots[Index]);

	Standard_Integer uLength = BSplCLib::KnotsLength(Seq_uKnots);

	TColStd_Array1OfReal uKnotVector(1, uLength);
	TColStd_Array1OfReal vKnotVector(1, 6);
	TColStd_Array1OfInteger uMult(1, uLength);
	TColStd_Array1OfInteger vMult(1, 6);

	BSplCLib::Knots(Seq_uKnots, uKnotVector, uMult);
	//BSplCLib::Knots(Seq_vKnots, vKnotVector, vMult);

	vMult.SetValue(1, 3);
	vMult.SetValue(2, 2);
	vMult.SetValue(3, 2);
	vMult.SetValue(4, 2);
	vMult.SetValue(5, 2);
	vMult.SetValue(6, 3);

	vKnotVector.SetValue(1, 0);
	vKnotVector.SetValue(2, 0.2);
	vKnotVector.SetValue(3, 0.4);
	vKnotVector.SetValue(4, 0.6);
	vKnotVector.SetValue(5, 0.8);
	vKnotVector.SetValue(6, 1.0);

	theHull_ = new Geom_BSplineSurface(*theControlNet_, *theWeightNet_, uKnotVector, vKnotVector, uMult, vMult, uDegree, vDegree);
}

