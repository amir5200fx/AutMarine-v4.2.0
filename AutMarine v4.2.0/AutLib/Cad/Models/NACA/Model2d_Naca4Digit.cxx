#include <Model2d_Naca4Digit.hxx>

#include <Geometry_Intersect.hxx>
#include <Cad2d_CurveOnPlane.hxx>
#include <Cad2d_Plane.hxx>
#include <TColCad2d_HAry1dOfCurveOnPlane.hxx>
#include <TColGeom_Ary1dOfPnt2d.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace GeoLib;

#include <Geom2d_BSplineCurve.hxx>
#include <Geom2d_Curve.hxx>
#include <gp_Ax2d.hxx>
#include <gp_Ax22d.hxx>
#include <Geom2dAPI_Interpolate.hxx>
#include <TColgp_HArray1OfPnt2d.hxx>

static const Standard_Integer DEFAULT_NB_OF_OFFSETS = 40;

AutLib::CadLib::Model2d_Naca4Digit::Model2d_Naca4Digit()
	: theNbOffsetPoints_(DEFAULT_NB_OF_OFFSETS)
{
}

Model2d_Naca4DigitParameters & AutLib::CadLib::Model2d_Naca4Digit::Parameters()
{
	return theParameters_;
}

const Model2d_Naca4DigitParameters & AutLib::CadLib::Model2d_Naca4Digit::Parameters() const
{
	return theParameters_;
}

void AutLib::CadLib::Model2d_Naca4Digit::SetNbOffsets(const Standard_Integer NbOffsetPoints)
{
	theNbOffsetPoints_ = NbOffsetPoints;
}

void AutLib::CadLib::Model2d_Naca4Digit::Perform()
{
	TColStd_Ary1dOfReal X, Yc, Yt, Ypc;

	const Standard_Integer NbSegments = theNbOffsetPoints_ - 1;

	Debug_If_Condition_Message(NbSegments < 1, " Invalid Nb. of segments");

	Try_Exception_Handle_Exit(X = Parameters(NbSegments));

	Yc = CamberOffsets(X);
	Yt = ThicknessDistribution(X);
	Ypc = CamberTangentDistribution(X);

	TColGeom_Ary1dOfPnt2d UP(NbSegments + 1);
	TColGeom_Ary1dOfPnt2d LP(NbSegments + 1);

	forThose
	(
		Index,
		0,
		NbSegments
	)
	{
		const Standard_Real Angle = atan(Ypc[Index]);
		const Standard_Real Cos = cos(Angle);
		const Standard_Real Sin = sin(Angle);

		/*UP[Index] = Geom_Pnt2d(X[Index] * theParameters_.Chord() - Yt[Index] * Sin, Yc[Index] + Yt[Index] * Cos);
		LP[Index] = Geom_Pnt2d(X[Index] * theParameters_.Chord() + Yt[Index] * Sin, Yc[Index] - Yt[Index] * Cos);*/

		UP[Index] = Geom_Pnt2d(X[Index] - Yt[Index] * Sin, Yc[Index] + Yt[Index] * Cos) * theParameters_.Chord();
		LP[Index] = Geom_Pnt2d(X[Index] + Yt[Index] * Sin, Yc[Index] - Yt[Index] * Cos) * theParameters_.Chord();
	}

	Geom_Pnt2d t1 = Geom_Pnt2d(UP[NbSegments].X() - UP[NbSegments - 1].X(), UP[NbSegments].Y() - UP[NbSegments - 1].Y());
	Geom_Pnt2d t2 = Geom_Pnt2d(LP[NbSegments].X() - LP[NbSegments - 1].X(), LP[NbSegments].Y() - LP[NbSegments - 1].Y());

	Geom_Pnt2d IP = Geometry_Intersect::IntersectionTwoLines(UP[NbSegments - 1], t1, LP[NbSegments - 1], t2);

	UP[NbSegments] = LP[NbSegments] = IP;

	Handle(TColgp_HArray1OfPnt2d) UP1 = new TColgp_HArray1OfPnt2d(1, UP.Size());
	forThose(Index, 0, MaxIndexOf(UP))
		UP1->SetValue(Index + 1, UP[Index]);

	Handle(TColgp_HArray1OfPnt2d) LP1 = new TColgp_HArray1OfPnt2d(1, LP.Size());
	forThose(Index, 0, MaxIndexOf(LP))
		LP1->SetValue(Index + 1, LP[Index]);

	Geom2dAPI_Interpolate Interpolation1(UP1, Standard_False, 1.0E-6);
	Interpolation1.Perform();

	Geom2dAPI_Interpolate Interpolation2(LP1, Standard_False, 1.0E-6);
	Interpolation2.Perform();

	theLower_ = (Handle(Geom2d_BSplineCurve))Interpolation1.Curve();
	theUpper_ = (Handle(Geom2d_BSplineCurve))Interpolation2.Curve();
}

Global_Handle(Cad2d_Plane) AutLib::CadLib::Model2d_Naca4Digit::ExportAsPart(const gp_Ax2d & A, const Standard_Boolean Sense) const
{
	return ExportAsPart(gp_Ax22d(A, Sense));
}

Global_Handle(Cad2d_Plane) AutLib::CadLib::Model2d_Naca4Digit::ExportAsPart(const gp_Ax22d & A) const
{
	Debug_If_Condition(theLower_.IsNull());
	Debug_If_Condition(theUpper_.IsNull());

	TColCad2d_HAry1dOfCurveOnPlane Curves(2);
	Curves[0] = new Cad2d_CurveOnPlane(theLower_->FirstParameter(), theLower_->LastParameter(), theLower_);
	Curves[1] = new Cad2d_CurveOnPlane(theUpper_->FirstParameter(), theUpper_->LastParameter(), theUpper_);

	Curves[0]->Reverse();

	Global_Handle(Cad2d_Plane) Plane = new Cad2d_Plane;
	Plane->Make(Curves);

	gp_Trsf2d T;
	T.SetTransformation(A.XAxis(), gp::OX2d());

	Plane->Transform(T);

	return Plane;
}

TColStd_Ary1dOfReal AutLib::CadLib::Model2d_Naca4Digit::Parameters(const Standard_Integer NbSegmets) const
{
	if (NbSegmets < 1) THROW_STANDARD_EXCEPTION(" Invalid Nb of segments");

	TColStd_Ary1dOfReal X(NbSegmets + 1);
	const Standard_Real Dx = PI / (Standard_Real)NbSegmets;

	forThose(Index, 0, NbSegmets)
		X[Index] = 0.5*(1.0 - cos(Index*Dx));

	MOVE(X);
}

TColStd_Ary1dOfReal AutLib::CadLib::Model2d_Naca4Digit::CamberOffsets(const TColStd_Ary1dOfReal & Parameters) const
{
	const Standard_Integer NbSegmets = Parameters.Size();

	TColStd_Ary1dOfReal Y(NbSegmets + 1);

	const Standard_Real MaxCamberPos = theParameters_.MaxCamberPosition() / 100.0;
	const Standard_Real MaxCamber = theParameters_.MaxCamber() / 100.0;

	Standard_Real Xc, Yc;

	forThose
	(
		Index,
		0,
		MaxIndexOf(Parameters)
	)
	{
		Xc = Parameters[Index];

		if (Xc <= MaxCamberPos)
			Yc = MaxCamber*(2 * MaxCamberPos*Xc - Xc*Xc) / (MaxCamberPos*MaxCamberPos);
		else
			Yc = MaxCamber*((1.0 - 2 * MaxCamberPos) + 2 * MaxCamberPos*Xc - Xc*Xc) / ((1.0 - MaxCamberPos)*(1.0 - MaxCamberPos));

		Y[Index] = Yc;
	}

	MOVE(Y);
}

TColStd_Ary1dOfReal AutLib::CadLib::Model2d_Naca4Digit::ThicknessDistribution(const TColStd_Ary1dOfReal & Parameters) const
{
	const Standard_Integer NbSegmets = Parameters.Size();
	const Standard_Real Thickness = theParameters_.MaxThickness() / 100.0;

	TColStd_Ary1dOfReal Y(NbSegmets + 1);

	forThose
	(
		Index,
		0,
		MaxIndexOf(Parameters)
	)
	{
		const Standard_Real X = Parameters[Index];
		const Standard_Real Sum = X*(-0.126 + X*(-0.3516 + X*(0.2843 - 0.1015*X)));

		Y[Index] = (Thickness / 0.2)*(0.2969*sqrt(X) + Sum);
	}

	MOVE(Y);
}

TColStd_Ary1dOfReal AutLib::CadLib::Model2d_Naca4Digit::CamberTangentDistribution(const TColStd_Ary1dOfReal & Parameters) const
{
	const Standard_Integer NbSegmets = Parameters.Size();

	TColStd_Ary1dOfReal Y(NbSegmets + 1);

	const Standard_Real MaxCamberPos = theParameters_.MaxCamberPosition() / 100.0;
	const Standard_Real MaxCamber = theParameters_.MaxCamber() / 100.0;

	forThose
	(
		Index,
		0,
		MaxIndexOf(Parameters)
	)
	{
		const Standard_Real X = Parameters[Index];

		if (X <= MaxCamberPos)
			Y[Index] = MaxCamber*(2 * MaxCamberPos - 2 * X) / (MaxCamberPos*MaxCamberPos);
		else
			Y[Index] = MaxCamber*(2 * MaxCamberPos - 2 * X) / ((1.0 - MaxCamberPos)*(1.0 - MaxCamberPos));
	}

	MOVE(Y);
}