#include <Duct_Hull.hxx>

#include <Geom_Pnt2d.hxx>
#include <Duct_ConstParameters.hxx>
#include <IO_Tecplot.hxx>

#include <Geom2d_Line.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColgp_Array1OfPnt2d.hxx>
#include <TColStd_Array1OfInteger.hxx>

using namespace AutLib;
using namespace CadLib;

#define Interpd1(X, Val0, Val1)  \
   (Val1 - Val0)*X + Val0;

#define SmoothingParameter(XLIST, nbSections, WEIGHT, LEVEL)  \
   forThose(Index, 1, LEVEL) {Smoothing(XLIST, WEIGHT, nbSections);}

namespace AutLib
{
	namespace CadLib
	{
		static void Smoothing
		(
			TColStd_Ary1dOfReal& Parameters,
			Standard_Real Coeff,
			Standard_Integer nbSections
		)
		{
			Try_Exception_Handle_Exit
			(
				forThose
				(
					Section,
					1,
					nbSections - 2
				)
			{
				Standard_Real Mean = MEAN
				(
					Parameters[Section - 1],
					Parameters[Section + 1]
				);

				Parameters[Section] += (Mean - Parameters[Section])*Coeff;
			}
			);
		}
	}
}

void AutLib::CadLib::Duct_Hull::CreateBredthProfile()
{
	const Duct_Dimensions & Dimensions = theParameters_.Dimensions();
	const Duct_BreadthForm & Breadth = theParameters_.Breadth();

	Standard_Real OveralLength = Dimensions.OveralLength();
	
	Geom_Pnt2d P0(0, Dimensions.BreadthAtInlet());
	Geom_Pnt2d P14(OveralLength, Dimensions.BreadthAtOutlet());

	Standard_Real BreadthAtMid = MEAN(Dimensions.BreadthAtInlet(), Dimensions.BreadthAtOutlet())*Breadth.MidWidth();

	Geom_Pnt2d P7(theParameters_.HullForm().MidLocation()*OveralLength, BreadthAtMid);

	Geom_Pnt2d P4(Breadth.LeftTurningPosition()*P7.X(), BreadthAtMid + Breadth.LeftTurningWidth()*(Dimensions.BreadthAtInlet() - BreadthAtMid));
	Geom_Pnt2d P10(P7.X() + Breadth.RightTurningPosition()*(OveralLength - P7.X()), BreadthAtMid + Breadth.RightTurningWidth()*(Dimensions.BreadthAtOutlet() - BreadthAtMid));

	Geom_Pnt2d P2(Breadth.InletOffset()*0.5*P4.X(), P0.Y());
	Geom_Pnt2d P12(OveralLength - Breadth.OutletOffset()*0.5*(P14.X() - P10.X()), P14.Y());

	Geom_Pnt2d P1 = MEAN(P0, P2);
	Geom_Pnt2d P13 = MEAN(P12, P14);

	Geom_Pnt2d P3(P2.X() + Breadth.InletWeight()*(P4.X() - P2.X()), P2.Y());
	Geom_Pnt2d P11(P12.X() + Breadth.OutletWeight()*(P10.X() - P12.X()), P12.Y());

	Geom_Pnt2d P6(P7.X() - Breadth.MidOffset()*0.5*(P7.X() - P4.X()), P7.Y());
	Geom_Pnt2d P8(P7.X() + Breadth.MidOffset()*0.5*(P10.X() - P7.X()), P7.Y());

	Geom_Pnt2d P5(P6.X() + Breadth.InletRiseWeight()*(P4.X() - P6.X()), P6.Y());
	Geom_Pnt2d P9(P8.X() + Breadth.OutletRiseWeight()*(P10.X() - P8.X()), P7.Y());

	Standard_Integer nbPoles = 15;

	TColgp_Array1OfPnt2d Points(1, 15);
	Points.SetValue(1, P0);
	Points.SetValue(2, P1);
	Points.SetValue(3, P2);
	Points.SetValue(4, P3);
	Points.SetValue(5, P4);
	Points.SetValue(6, P5);
	Points.SetValue(7, P6);
	Points.SetValue(8, P7);
	Points.SetValue(9, P8);
	Points.SetValue(10, P9);
	Points.SetValue(11, P10);
	Points.SetValue(12, P11);
	Points.SetValue(13, P12);
	Points.SetValue(14, P13);
	Points.SetValue(15, P14);

	TColStd_Array1OfReal Weights(1, nbPoles);
	Weights.Init(1);

	Standard_Integer
		MaxIndex,
		Degree;

	MaxIndex = nbPoles - 1;
	Degree = 2;

	TColStd_Array1OfReal Knots(1, 8);
	TColStd_Array1OfInteger Mults(1, 8);

	Knots.SetValue(1, 0);
	Knots.SetValue(2, OveralLength / (Standard_Real)7);
	Knots.SetValue(3, (Standard_Real)2 * OveralLength / (Standard_Real)7);
	Knots.SetValue(4, (Standard_Real)3 * OveralLength / (Standard_Real)7);
	Knots.SetValue(5, (Standard_Real)4 * OveralLength / (Standard_Real)7);
	Knots.SetValue(6, (Standard_Real)5 * OveralLength / (Standard_Real)7);
	Knots.SetValue(7, (Standard_Real)6 * OveralLength / (Standard_Real)7);
	Knots.SetValue(8, OveralLength);

	Mults.SetValue(1, 3);
	Mults.SetValue(2, 2);
	Mults.SetValue(3, 2);
	Mults.SetValue(4, 2);
	Mults.SetValue(5, 2);
	Mults.SetValue(6, 2);
	Mults.SetValue(7, 2);
	Mults.SetValue(8, 3);

	Handle(Geom2d_BSplineCurve) BreadthCurve = new Geom2d_BSplineCurve(Points, Weights, Knots, Mults, Degree);
	theProfiles_.SetBreadth(BreadthCurve);
}

void AutLib::CadLib::Duct_Hull::CreateDepthProfile()
{
	const Duct_Dimensions & Dimensions = theParameters_.Dimensions();
	const Duct_BreadthForm & Depth = theParameters_.Depth();

	Standard_Real OveralLength = Dimensions.OveralLength();

	Geom_Pnt2d P0(0, Dimensions.DepthAtInlet());
	Geom_Pnt2d P14(OveralLength, Dimensions.DepthAtOutlet());

	Standard_Real DepthAtMid = MEAN(Dimensions.DepthAtInlet(), Dimensions.DepthAtOutlet())*Depth.MidWidth();

	Geom_Pnt2d P7(theParameters_.HullForm().MidLocation()*OveralLength, DepthAtMid);

	Geom_Pnt2d P4(Depth.LeftTurningPosition()*P7.X(), DepthAtMid + Depth.LeftTurningWidth()*(Dimensions.DepthAtInlet() - DepthAtMid));
	Geom_Pnt2d P10(P7.X() + Depth.RightTurningPosition()*(OveralLength - P7.X()), DepthAtMid + Depth.RightTurningWidth()*(Dimensions.DepthAtOutlet() - DepthAtMid));

	Geom_Pnt2d P2(Depth.InletOffset()*0.5*P4.X(), P0.Y());
	Geom_Pnt2d P12(OveralLength - Depth.OutletOffset()*0.5*(P14.X() - P10.X()), P14.Y());

	Geom_Pnt2d P1 = MEAN(P0, P2);
	Geom_Pnt2d P13 = MEAN(P12, P14);

	Geom_Pnt2d P3(P2.X() + Depth.InletWeight()*(P4.X() - P2.X()), P2.Y());
	Geom_Pnt2d P11(P12.X() + Depth.OutletWeight()*(P10.X() - P12.X()), P12.Y());

	Geom_Pnt2d P6(P7.X() - Depth.MidOffset()*0.5*(P7.X() - P4.X()), P7.Y());
	Geom_Pnt2d P8(P7.X() + Depth.MidOffset()*0.5*(P10.X() - P7.X()), P7.Y());

	Geom_Pnt2d P5(P6.X() + Depth.InletRiseWeight()*(P4.X() - P6.X()), P6.Y());
	Geom_Pnt2d P9(P8.X() + Depth.OutletRiseWeight()*(P10.X() - P8.X()), P7.Y());

	Standard_Integer nbPoles = 15;

	TColgp_Array1OfPnt2d Points(1, 15);
	Points.SetValue(1, P0);
	Points.SetValue(2, P1);
	Points.SetValue(3, P2);
	Points.SetValue(4, P3);
	Points.SetValue(5, P4);
	Points.SetValue(6, P5);
	Points.SetValue(7, P6);
	Points.SetValue(8, P7);
	Points.SetValue(9, P8);
	Points.SetValue(10, P9);
	Points.SetValue(11, P10);
	Points.SetValue(12, P11);
	Points.SetValue(13, P12);
	Points.SetValue(14, P13);
	Points.SetValue(15, P14);

	TColStd_Array1OfReal Weights(1, nbPoles);
	Weights.Init(1);

	Standard_Integer
		MaxIndex,
		Degree;

	MaxIndex = nbPoles - 1;
	Degree = 2;

	TColStd_Array1OfReal Knots(1, 8);
	TColStd_Array1OfInteger Mults(1, 8);

	Knots.SetValue(1, 0);
	Knots.SetValue(2, OveralLength / (Standard_Real)7);
	Knots.SetValue(3, (Standard_Real)2 * OveralLength / (Standard_Real)7);
	Knots.SetValue(4, (Standard_Real)3 * OveralLength / (Standard_Real)7);
	Knots.SetValue(5, (Standard_Real)4 * OveralLength / (Standard_Real)7);
	Knots.SetValue(6, (Standard_Real)5 * OveralLength / (Standard_Real)7);
	Knots.SetValue(7, (Standard_Real)6 * OveralLength / (Standard_Real)7);
	Knots.SetValue(8, OveralLength);

	Mults.SetValue(1, 3);
	Mults.SetValue(2, 2);
	Mults.SetValue(3, 2);
	Mults.SetValue(4, 2);
	Mults.SetValue(5, 2);
	Mults.SetValue(6, 2);
	Mults.SetValue(7, 2);
	Mults.SetValue(8, 3);

	Handle(Geom2d_BSplineCurve) DepthCurve = new Geom2d_BSplineCurve(Points, Weights, Knots, Mults, Degree);
	theProfiles_.SetDepth(DepthCurve);
}

void AutLib::CadLib::Duct_Hull::CreateProfiles()
{
	CreateBredthProfile();

	CreateDepthProfile();
}

void AutLib::CadLib::Duct_Hull::CalcxXSections()
{
	const Duct_Dimensions & Dimensions = theParameters_.Dimensions();

	Standard_Integer
		nbSections,
		Section;

	Standard_Real
		dx;

	Get_Object(XCoords) = theXParameters_.XCoords();

	nbSections = Dimensions.NbSections();

	dx = Dimensions.OveralLength() / (Standard_Real)(nbSections - 1);
	forThose
	(
		Index,
		0,
		nbSections - 1
	)
	{
		Section = Index;
		XCoords[Section] = Index*dx;
	}
}

void AutLib::CadLib::Duct_Hull::CalcxYSections()
{
	const Duct_Dimensions & Dimensions = theParameters_.Dimensions();

	if (theProfiles_.Breadth().IsNull())
	{
		THROW_STANDARD_EXCEPTION(" No Breadth Profile has been found");
	}

	Standard_Integer nbSections = Dimensions.NbSections();

	Get_Const_Object(xSections) = theXParameters_.XCoords();
	Get_Object(YCoords) = theXParameters_.YCoords();

	Geom_Pnt2d Point;
	Geom2dAPI_InterCurveCurve Intersection;

	forThose
	(
		Section,
		1,
		nbSections - 2
	)
	{
		Standard_Real X = xSections[Section];

		Handle(Geom2d_Line) Line = new Geom2d_Line(gp_Pnt2d(X, 0), gp_Dir2d(0, 1));

		Intersection.Init(theProfiles_.Breadth(), Line, 1.0e-6);

		if (NOT Intersection.NbPoints())
		{
			THROW_STANDARD_EXCEPTION(" No Intersection has been found");
		}

		if (Intersection.NbPoints() != 1)
		{
			THROW_STANDARD_EXCEPTION(" More than one intersection point has been found");
		}

		Point = Intersection.Point(1);

		YCoords[Section] = Point.Y();
	}

	YCoords.SetFirst(theProfiles_.Breadth()->Value(theProfiles_.Breadth()->FirstParameter()).Y());
	YCoords.SetLast(theProfiles_.Breadth()->Value(theProfiles_.Breadth()->LastParameter()).Y());
}

void AutLib::CadLib::Duct_Hull::CalcxZSections()
{
	const Duct_Dimensions & Dimensions = theParameters_.Dimensions();
	const Duct_GeneratorLineForm & Generator = theParameters_.Generator();

	Standard_Integer nbSections = Dimensions.NbSections();

	Get_Const_Object(XCoords) = theXParameters_.XCoords();
	Get_Object(ZCoords) = theXParameters_.ZCoords();

	Standard_Real Length = XCoords[nbSections - 1];

	Standard_Real
		XRise,
		XPos,
		XVel0,
		XVel1;

	XRise = Generator.RisePoint()*Length;
	XPos = Generator.Position()*Length;
	XVel0 = Generator.OutletTangent()*XPos;
	XVel1 = XRise + Generator.RiseTangent()*(XPos - XRise);

	Standard_Real
		Parameter,
		xSection;

	forThose
	(
		Section,
		0,
		nbSections - 1
	)
	{
		xSection = XCoords(Section);

		if (xSection <= XVel0)
		{
			ZCoords[Section] = Dimensions.HeightAtOutlet();
		}
		else if (xSection >= XVel1)
		{
			ZCoords[Section] = ZERO;
		}
		else
		{
			Parameter = (xSection - XVel1) / (XVel0 - XVel1);

			Standard_Real Value = Interpd1
			(
				Parameter,
				ZERO,
				Dimensions.HeightAtOutlet()
			);

			ZCoords[Section] = Value;
		}
	}

	if (Apply_Smoothing_)
	{
		SmoothingParameter
		(
			ZCoords,
			nbSections,
			Duct_ConstParameters::SmoothWeight(),
			Duct_ConstParameters::LevelOfSmoothing()
		);
	}
}

void AutLib::CadLib::Duct_Hull::CalcxDepth()
{
	const Duct_Dimensions & Dimensions = theParameters_.Dimensions();

	if (theProfiles_.Depth().IsNull())
	{
		THROW_STANDARD_EXCEPTION(" No Depth Profile has been found");
	}

	Standard_Integer nbSections = Dimensions.NbSections();

	Get_Const_Object(xSections) = theXParameters_.XCoords();
	Get_Object(XDepth) = theXParameters_.Depth();

	Geom_Pnt2d Point;
	Geom2dAPI_InterCurveCurve Intersection;

	forThose
	(
		Section,
		1,
		nbSections - 2
	)
	{
		Standard_Real X = xSections[Section];

		Handle(Geom2d_Line) Line = new Geom2d_Line(gp_Pnt2d(X, 0), gp_Dir2d(0, 1));

		Intersection.Init(theProfiles_.Depth(), Line, 1.0e-6);

		if (NOT Intersection.NbPoints())
		{
			THROW_STANDARD_EXCEPTION(" No Intersection has been found");
		}

		if (Intersection.NbPoints() != 1)
		{
			THROW_STANDARD_EXCEPTION(" More than one intersection point has been found");
		}

		Point = Intersection.Point(1);

		XDepth[Section] = Point.Y();
	}

	XDepth.SetFirst(theProfiles_.Depth()->Value(theProfiles_.Depth()->FirstParameter()).Y());
	XDepth.SetLast(theProfiles_.Depth()->Value(theProfiles_.Depth()->LastParameter()).Y());
}

void AutLib::CadLib::Duct_Hull::CalcxUpperTightness()
{
	const Duct_Dimensions & Dimensions = theParameters_.Dimensions();
	const Duct_HullForm & Hull = theParameters_.HullForm();

	Get_Const_Object(XCoords) = theXParameters_.XCoords();
	Get_Object(XTightness) = theXParameters_.UpperTightness();

	Standard_Integer nbSections = Dimensions.NbSections();

	Standard_Real Length = XCoords(nbSections - 1);

	forThose
	(
		Section,
		0,
		nbSections - 1
	)
	{
		Standard_Real X = XCoords(Section) / Length;

		if (X < (Standard_Real)0.5)
		{
			Standard_Real Value = Interpd1
			(
				(Standard_Real)2.0*X,
				Hull.InletForm().UpperTightness(),
				Hull.MidForm().UpperTightness()
			);

			XTightness.SetValue(Section, Value);
		}
		else
		{
			Standard_Real Value = Interpd1
			(
				(Standard_Real)2.0 * (X - (Standard_Real)0.5),
				Hull.MidForm().UpperTightness(),
				Hull.OutletForm().UpperTightness()
			);

			XTightness.SetValue(Section, Value);
		}
	}

	if (Apply_Smoothing_)
	{
		SmoothingParameter
		(
			theXParameters_.UpperTightness(),
			nbSections,
			Duct_ConstParameters::SmoothWeight(),
			Duct_ConstParameters::LevelOfSmoothing()
		);
	}
}

void AutLib::CadLib::Duct_Hull::CalcxLowerTightness()
{
	const Duct_Dimensions & Dimensions = theParameters_.Dimensions();
	const Duct_HullForm & Hull = theParameters_.HullForm();

	Get_Const_Object(XCoords) = theXParameters_.XCoords();
	Get_Object(XTightness) = theXParameters_.LowerTightness();

	Standard_Integer nbSections = Dimensions.NbSections();

	Standard_Real Length = XCoords(nbSections - 1);

	forThose
	(
		Section,
		0,
		nbSections - 1
	)
	{
		Standard_Real X = XCoords(Section) / Length;

		if (X < (Standard_Real)0.5)
		{
			Standard_Real Value = Interpd1
			(
				(Standard_Real)2.0*X,
				Hull.InletForm().LowerTightness(),
				Hull.MidForm().LowerTightness()
			);

			XTightness.SetValue(Section, Value);
		}
		else
		{
			Standard_Real Value = Interpd1
			(
				(Standard_Real)2.0 * (X - (Standard_Real)0.5),
				Hull.MidForm().LowerTightness(),
				Hull.OutletForm().LowerTightness()
			);

			XTightness.SetValue(Section, Value);
		}
	}

	if (Apply_Smoothing_)
	{
		SmoothingParameter
		(
			theXParameters_.LowerTightness(),
			nbSections,
			Duct_ConstParameters::SmoothWeight(),
			Duct_ConstParameters::LevelOfSmoothing()
		);
	}
}

void AutLib::CadLib::Duct_Hull::CalcxSideSlope()
{
	const Duct_Dimensions & Dimensions = theParameters_.Dimensions();
	const Duct_HullForm & Hull = theParameters_.HullForm();

	Get_Const_Object(XCoords) = theXParameters_.XCoords();
	Get_Object(XSide) = theXParameters_.SideSlope();

	Standard_Integer nbSections = Dimensions.NbSections();

	Standard_Real Length = Dimensions.OveralLength();

	forThose
	(
		Section,
		0,
		nbSections - 1
	)
	{
		Standard_Real X = XCoords(Section) / Length;

		if (X < (Standard_Real)0.5)
		{
			Standard_Real Value = Interpd1
			(
				(Standard_Real)2.0*X,
				Hull.InletForm().SideSlope(),
				Hull.MidForm().SideSlope()
			);

			XSide.SetValue(Section, Value);
		}
		else
		{
			Standard_Real Value = Interpd1
			(
				(Standard_Real)2.0 * (X - (Standard_Real)0.5),
				Hull.MidForm().SideSlope(),
				Hull.OutletForm().SideSlope()
			);

			XSide.SetValue(Section, Value);
		}
	}

	if (Apply_Smoothing_)
	{
		SmoothingParameter
		(
			theXParameters_.SideSlope(),
			nbSections,
			Duct_ConstParameters::SmoothWeight(),
			Duct_ConstParameters::LevelOfSmoothing()
		);
	}
}

void AutLib::CadLib::Duct_Hull::CalcxWidth()
{
	const Duct_Dimensions & Dimensions = theParameters_.Dimensions();
	const Duct_HullForm & Hull = theParameters_.HullForm();

	Get_Const_Object(XCoords) = theXParameters_.XCoords();
	Get_Object(XWidth) = theXParameters_.Width();

	Standard_Integer nbSections = Dimensions.NbSections();

	Standard_Real Length = Dimensions.OveralLength();

	forThose
	(
		Section,
		0,
		nbSections - 1
	)
	{
		Standard_Real X = XCoords(Section) / Length;

		if (X < (Standard_Real)0.5)
		{
			Standard_Real Value = Interpd1
			(
				(Standard_Real)2.0*X,
				Hull.InletForm().Width(),
				Hull.MidForm().Width()
			);

			XWidth.SetValue(Section, Value);
		}
		else
		{
			Standard_Real Value = Interpd1
			(
				(Standard_Real)2.0 * (X - (Standard_Real)0.5),
				Hull.MidForm().Width(),
				Hull.OutletForm().Width()
			);

			XWidth.SetValue(Section, Value);
		}
	}

	if (Apply_Smoothing_)
	{
		SmoothingParameter
		(
			theXParameters_.Width(),
			nbSections,
			Duct_ConstParameters::SmoothWeight(),
			Duct_ConstParameters::LevelOfSmoothing()
		);
	}
}

void AutLib::CadLib::Duct_Hull::CalcxParameters()
{
	Try_Exception_Handle_Exit(CalcxYSections());

	Try_Exception_Handle_Exit(CalcxZSections());

	Try_Exception_Handle_Exit(CalcxDepth());

	Try_Exception_Handle_Exit(CalcxLowerTightness());

	Try_Exception_Handle_Exit(CalcxUpperTightness());

	Try_Exception_Handle_Exit(CalcxSideSlope());

	Try_Exception_Handle_Exit(CalcxSideSlope());

	Try_Exception_Handle_Exit(CalcxWidth());
}