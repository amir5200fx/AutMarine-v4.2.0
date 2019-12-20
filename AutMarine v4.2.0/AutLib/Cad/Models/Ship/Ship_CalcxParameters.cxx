#include <Ship_Hull.hxx>

#include <Geom_Pnt2d.hxx>
#include <Ship_ConstParameters.hxx>

using namespace AutLib;
using namespace CadLib;

#include <Geom2d_Line.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>

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

void AutLib::CadLib::Ship_Hull::CalcxXSections()
{
	const Ship_Dimensions & Dimensions = theParameters_.Dimensions();

	Standard_Integer
		nbSections,
		Section;

	Standard_Real
		dx,
		AftCoeff,
		FwdCoeff,
		dxA,
		dxF;

	AftCoeff = Ship_ConstParameters::AftComp();
	FwdCoeff = Ship_ConstParameters::FwdComp();

	nbSections = Dimensions.NbNetColumns();

	//Exclusion stem pair
	nbSections--;

	dx = Dimensions.LengthOnDeck() / (Standard_Real)(nbSections - 1);

	nbSections++;

	Get_Object(XCoords) = theXParameters_.XCoords();

	Section = 0;
	XCoords[Section] = 0;

	Section = nbSections - 1;
	XCoords[Section] = MIN(nbSections*dx, Dimensions.LengthOnDeck());

	Section = nbSections - 2;
	XCoords[Section] = MIN(nbSections*dx, Dimensions.LengthOnDeck());

	dxA = (ONE - AftCoeff)*dx;
	dxF = (ONE - FwdCoeff)*dx;

	Standard_Real
		x0,
		x1;

	x0 = dxA;
	x1 = Dimensions.LengthOnDeck() - dxF;

	dx = (x1 - x0) / (Standard_Real)(nbSections - 4);

	forThose
	(
		Index,
		0,
		nbSections - 4
	)
	{
		Section = Index + 1;
		XCoords[Section] = Index*dx + x0;
	}
}

void AutLib::CadLib::Ship_Hull::CalcxYSections()
{
	const Ship_Dimensions & Dimensions = theParameters_.Dimensions();

	if (theProfiles_.Deck().IsNull())
	{
		THROW_STANDARD_EXCEPTION(" No Deck Profile has been found");
	}

	Standard_Integer nbSections = Dimensions.NbNetColumns();

	Get_Const_Object(xSections) = theXParameters_.XCoords();
	Get_Object(YCoords) = theXParameters_.YCoords();

	Geom_Pnt2d Point;
	Geom2dAPI_InterCurveCurve Intersection;

	forThose
	(
		Section,
		0,
		nbSections - 1
	)
	{
		Standard_Real X = xSections[Section];

		Handle(Geom2d_Line) Line = new Geom2d_Line(gp_Pnt2d(X, 0), gp_Dir2d(0, 1));

		Intersection.Init(theProfiles_.Deck(), Line, 1.0e-6);

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
}

void AutLib::CadLib::Ship_Hull::CalcxZSections()
{
	const Ship_Dimensions & Dimensions = theParameters_.Dimensions();
	const Ship_KeelForm & Keel = theParameters_.Keel();

	Standard_Integer nbSections = Dimensions.NbNetColumns();

	Get_Const_Object(XCoords) = theXParameters_.XCoords();
	Get_Object(ZCoords) = theXParameters_.ZCoords();

	Standard_Real Length = XCoords[nbSections - 3];

	Standard_Real
		XRise,
		XPos,
		XVel0,
		XVel1;

	XRise = Keel.KeelRisePoint()*Length;
	XPos = Keel.KeelPosition()*Length;
	XVel0 = Keel.KeelTransomTangent()*XPos;
	XVel1 = XRise + Keel.KeelRiseTangent()*(XPos - XRise);

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
			ZCoords[Section] = Dimensions.TransomHeight();
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
				Dimensions.TransomHeight()
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
			Ship_ConstParameters::SmoothWeight(),
			Ship_ConstParameters::LevelOfSmoothing()
		);
	}
}

void AutLib::CadLib::Ship_Hull::CalcxDepthSections()
{
	const Ship_Dimensions & Dimensions = theParameters_.Dimensions();

	Standard_Real Length = Dimensions.LengthOnDeck();
	Standard_Real DepthAtBow = Dimensions.DepthAtBow();
	Standard_Real DepthAtTransom = Dimensions.DepthAtTransom();

	Get_Const_Object(XCoords) = theXParameters_.XCoords();
	Get_Object(XDepth) = theXParameters_.Depth();

	forThose
	(
		Section,
		0,
		Dimensions.NbNetColumns() - 1
	)
	{
		Standard_Real Parameter = XCoords(Section) / Length;

		Standard_Real Value = Interpd1
		(
			Parameter,
			DepthAtTransom,
			DepthAtBow
		);

		XDepth.SetValue(Section, Value);
	}
}

void AutLib::CadLib::Ship_Hull::CalcxDeadRise()
{
	const Ship_Dimensions & Dimensions = theParameters_.Dimensions();
	const Ship_HullForm & Hull = theParameters_.Hull();

	Standard_Integer nbSections = Dimensions.NbNetColumns();

	Get_Const_Object(XCoords) = theXParameters_.XCoords();
	Get_Object(XDead) = theXParameters_.DeadRise();

	Standard_Real Length = XCoords(nbSections - 3);

	forThose
	(
		Section,
		0,
		nbSections - 3
	)
	{
		Standard_Real X = XCoords(Section) / Length;

		if (X < (Standard_Real)0.5)
		{
			Standard_Real Value = Interpd1
			(
				(Standard_Real)2.0*X,
				Hull.AftForm().DeadRise(),
				Hull.MidForm().DeadRise()
			);

			XDead.SetValue(Section, Value);
		}
		else
		{
			Standard_Real Value = Interpd1
			(
				(Standard_Real)2.0 * (X - (Standard_Real)0.5),
				Hull.MidForm().DeadRise(),
				Hull.FwdForm().DeadRise()
			);

			XDead.SetValue(Section, Value);
		}
	}

	if (Apply_Smoothing_)
	{
		SmoothingParameter
		(
			theXParameters_.DeadRise(),
			nbSections - 2,
			Ship_ConstParameters::SmoothWeight(),
			Ship_ConstParameters::LevelOfSmoothing()
		);
	}
}

void AutLib::CadLib::Ship_Hull::CalcxFlare()
{
	const Ship_Dimensions & Dimensions = theParameters_.Dimensions();
	const Ship_HullForm & Hull = theParameters_.Hull();

	Get_Const_Object(XCoords) = theXParameters_.XCoords();
	Get_Object(XFlare) = theXParameters_.Flare();

	Standard_Integer nbSections = Dimensions.NbNetColumns();

	Standard_Real Length = Dimensions.LengthOnDeck();

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
				Hull.AftForm().Flare(),
				Hull.MidForm().Flare()
			);

			XFlare.SetValue(Section, Value);
		}
		else
		{
			Standard_Real Value = Interpd1
			(
				(Standard_Real)2.0 * (X - (Standard_Real)0.5),
				Hull.MidForm().Flare(),
				Hull.FwdForm().Flare()
			);

			XFlare.SetValue(Section, Value);
		}
	}

	if (Apply_Smoothing_)
	{
		SmoothingParameter
		(
			theXParameters_.Flare(),
			nbSections - 1,
			Ship_ConstParameters::SmoothWeight(),
			Ship_ConstParameters::LevelOfSmoothing()
		);
	}
}

void AutLib::CadLib::Ship_Hull::CalcxSideSlope()
{
	const Ship_Dimensions & Dimensions = theParameters_.Dimensions();
	const Ship_HullForm & Hull = theParameters_.Hull();

	Get_Const_Object(XCoords) = theXParameters_.XCoords();
	Get_Object(XSide) = theXParameters_.SideSlope();

	Standard_Integer nbSections = Dimensions.NbNetColumns();

	Standard_Real Length = Dimensions.LengthOnDeck();

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
				Hull.AftForm().SideSlope(),
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
				Hull.FwdForm().SideSlope()
			);

			XSide.SetValue(Section, Value);
		}
	}

	if (Apply_Smoothing_)
	{
		SmoothingParameter
		(
			theXParameters_.SideSlope(),
			nbSections - 1,
			Ship_ConstParameters::SmoothWeight(),
			Ship_ConstParameters::LevelOfSmoothing()
		);
	}
}

void AutLib::CadLib::Ship_Hull::CalcxTightness()
{
	const Ship_Dimensions & Dimensions = theParameters_.Dimensions();
	const Ship_HullForm & Hull = theParameters_.Hull();

	Get_Const_Object(XCoords) = theXParameters_.XCoords();
	Get_Object(XTightness) = theXParameters_.Tightness();

	Standard_Integer nbSections = Dimensions.NbNetColumns();

	Standard_Real Length = XCoords(nbSections - 3);

	forThose
	(
		Section,
		0,
		nbSections - 3
	)
	{
		Standard_Real X = XCoords(Section) / Length;

		if (X < (Standard_Real)0.5)
		{
			Standard_Real Value = Interpd1
			(
				(Standard_Real)2.0*X,
				Hull.AftForm().Tightness(),
				Hull.MidForm().Tightness()
			);

			XTightness.SetValue(Section, Value);
		}
		else
		{
			Standard_Real Value = Interpd1
			(
				(Standard_Real)2.0 * (X - (Standard_Real)0.5),
				Hull.MidForm().Tightness(),
				Hull.FwdForm().Tightness()
			);

			XTightness.SetValue(Section, Value);
		}
	}

	if (Apply_Smoothing_)
	{
		SmoothingParameter
		(
			theXParameters_.Tightness(),
			nbSections - 2,
			Ship_ConstParameters::SmoothWeight(),
			Ship_ConstParameters::LevelOfSmoothing()
		);
	}
}

void AutLib::CadLib::Ship_Hull::CalcxRake()
{
	const Ship_Dimensions & Dimensions = theParameters_.Dimensions();

	Standard_Integer nbSections = Dimensions.NbNetColumns();

	Get_Const_Object(XCoords) = theXParameters_.XCoords();
	Get_Object(XRake) = theXParameters_.Rake();

	Standard_Real
		Length,
		xSection;

	Length = Dimensions.LengthOnDeck();

	forThose
	(
		Section,
		0,
		nbSections - 1
	)
	{
		xSection = XCoords(Section) / Length;

		Standard_Real Value = Interpd1
		(
			xSection,
			theParameters_.Transom().Rake(),
			theParameters_.Stem().Rake()
		);

		XRake.SetValue(Section, Value);
	}
}

void AutLib::CadLib::Ship_Hull::CalcXSheer()
{
	theXParameters_.Sheer().Init(0);
}

void AutLib::CadLib::Ship_Hull::CalcxParameters()
{
	CreateDeckProfile();

	Try_Exception_Handle_Exit(CalcxYSections());

	Try_Exception_Handle_Exit(CalcxZSections());

	Try_Exception_Handle_Exit(CalcxDepthSections());

	Try_Exception_Handle_Exit(CalcxDeadRise());

	Try_Exception_Handle_Exit(CalcxSideSlope());

	Try_Exception_Handle_Exit(CalcxTightness());

	Try_Exception_Handle_Exit(CalcxFlare());

	Try_Exception_Handle_Exit(CalcxRake());

	CalcXSheer();
}