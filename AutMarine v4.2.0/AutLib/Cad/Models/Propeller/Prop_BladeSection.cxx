#include <Prop_BladeSection.hxx>
#include <Prop_Propeller.hxx>

#include <Geometry_Intersect.hxx>
#include <Prop_ExpandedView.hxx>
#include <TColGeom_Ary1dOfPnt2d.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace GeoLib;

AutLib::CadLib::Prop_BladeSection::Prop_BladeSection()
{
}

AutLib::CadLib::Prop_BladeSection::Prop_BladeSection
(
	const Handle(Geom2d_Curve)& theFace,
	const Handle(Geom2d_Curve)& theBack
)
	: theFace_(theFace)
	, theBack_(theBack)
{
}

void AutLib::CadLib::Prop_BladeSection::Init
(
	const Handle(Geom2d_Curve)& theFace,
	const Handle(Geom2d_Curve)& theBack
)
{
	theFace_ = theFace;
	theBack_ = theBack;
}

void AutLib::CadLib::Prop_BladeSection::SetFace(const Handle(Geom2d_Curve)& theFace)
{
	theFace_ = theFace;
}

void AutLib::CadLib::Prop_BladeSection::SetBack(const Handle(Geom2d_Curve)& theBack)
{
	theBack_ = theBack;
}

void AutLib::CadLib::Prop_Propeller::CreateSections_NACA4Digits()
{
	Standard_Integer NbSections = theParameters_.NbSections();
	forThose(Index, 0, NbSections - 1)
		CreateSectionProfiles_NACA4Digits(Index);
}

void AutLib::CadLib::Prop_Propeller::CreateSectionProfiles_NACA4Digits(int section)
{
	Standard_Integer n = theParameters_.NbSpans();
	Standard_Real xCamber = theXParameters_.xMaxCamber(section);
	Standard_Real xCamberPosition = theXParameters_.xMaxCamberPosition(section);

	Standard_Real Yc, Yt, Ypc, x, angle;
	Standard_Real dx = M_PI / (Standard_Real)(n - 1);

	TColStd_Ary1dOfReal X(n);
	TColGeom_Ary1dOfPnt2d TB(n), TF(n);

	forThose
	(
		Index,
		0,
		n - 1
	)
	{
		X.SetValue(Index, 0.5*(1.0 - cos(Index*dx)));
	}
	X.Last() = (1.0 - theParameters_.TEGap());

	forThose
	(
		Index,
		0, 
		n - 1
	)
	{
		if (X.Value(Index) <= xCamberPosition)
		{
			Yc = xCamber*(2 * xCamberPosition*X[Index] - X[Index] * X[Index]) / (xCamberPosition*xCamberPosition);
			Ypc = xCamber*(2 * xCamberPosition - 2 * X[Index]) / (xCamberPosition*xCamberPosition);
		}
		else
		{
			Yc = xCamber*((1.0 - 2 * xCamberPosition) + 2 * xCamberPosition*X[Index] - X[Index] * X[Index]) / ((1.0 - xCamberPosition)*(1.0 - xCamberPosition));
			Ypc = xCamber*(2 * xCamberPosition - 2 * X[Index]) / ((1.0 - xCamberPosition)*(1.0 - xCamberPosition));
		}

		x = X[Index];

		Standard_Real x2 = x*x;
		Standard_Real x3 = x2*x;
		Standard_Real x4 = x3*x;

		Yt = (theXParameters_.xThickness(section) / 0.2)*(0.2969*sqrt(x) - 0.1260*x - 0.3516*x2 + 0.2843*x3 - 0.1015*x4);

		angle = atan(Ypc);

		TB[Index].X() = x*theXParameters_.xChord(section) - Yt*sin(angle);
		TF[Index].X() = x*theXParameters_.xChord(section) + Yt*sin(angle);

		TB[Index].Y() = -Yc - Yt*cos(angle);
		TF[Index].Y() = -Yc + Yt*cos(angle);
	}

	/*Geom_Pnt2d t1 = Geom_Pnt2d(TB[n - 1].X() - TB[n - 2].X(), TB[n - 1].Y() - TB[n - 2].Y());
	Geom_Pnt2d t2 = Geom_Pnt2d(TF[n - 1].X() - TF[n - 2].X(), TF[n - 1].Y() - TF[n - 2].Y());

	Geom_Pnt2d IP = Geometry_Intersect::IntersectionTwoLines(TB[n - 2], t1, TF[n - 2], t2);

	TB[n - 1] = TF[n - 1] = IP;*/

	CreateExpandedView(section, TF, TB);
}

void AutLib::CadLib::Prop_Propeller::CreateExpandedView
(
	const Standard_Integer Section,
	const TColGeom_Ary1dOfPnt2d & theTF, 
	const TColGeom_Ary1dOfPnt2d & theTB
)
{
	Global_Handle(Prop_ExpandedView) ExpandedView = new Prop_ExpandedView(theParameters_.NbSpans());

	Get_Object(Expanded) = *ExpandedView;

	forThose
	(
		Index, 
		0,
		MaxIndexOf(theTF)
	)
	{
		Expanded.SetX(Index, 0.5*theXParameters_.xChord(Section) - (theTF[Index].X() + theXParameters_.xSkew(Section)));
		Expanded.SetXS(Index, 0.5*theXParameters_.xChord(Section) - theTF[Index].X());
		Expanded.SetTB(Index, theTB.Value(Index).Y());
		Expanded.SetTF(Index, theTF.Value(Index).Y());
		Expanded.SetYB(Index, theTB.Value(Index).Y() + theXParameters_.X(Index));
		Expanded.SetYF(Index, theTF.Value(Index).Y() + theXParameters_.X(Index));
	}
	thePropView_.SetExpandedView(Section, ExpandedView);
}