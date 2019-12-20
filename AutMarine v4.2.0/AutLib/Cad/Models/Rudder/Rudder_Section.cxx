#include <Rudder_Section.hxx>

#include <TColGeom_Ary1dOfPnt3d.hxx>

using namespace AutLib;

static const Standard_Real DEFAULT_TE_GAP = 0.002;

#include <GeomAPI_Interpolate.hxx>
#include <Geom_BSplineCurve.hxx>
#include <TColgp_HArray1OfPnt.hxx>

AutLib::CadLib::Rudder_Section::Rudder_Section()
	: theTEGap_(DEFAULT_TE_GAP)
	, IsDone_(Standard_False)
{
}

void AutLib::CadLib::Rudder_Section::SetNbOffsets(const Standard_Integer NbOffsetPoints)
{
	theNbOffsetPoints_ = NbOffsetPoints;
}

void AutLib::CadLib::Rudder_Section::SetChord(const Standard_Real theValue)
{
	theChord_ = theValue;
}

void AutLib::CadLib::Rudder_Section::SetThickness(const Standard_Real theValue)
{
	theThickness_ = theValue;
}

void AutLib::CadLib::Rudder_Section::Perform()
{
	TColStd_Ary1dOfReal X, Yt;

	const Standard_Integer NbSegments = theNbOffsetPoints_ - 1;

	Debug_If_Condition_Message(NbSegments < 1, " Invalid Nb. of segments");

	Try_Exception_Handle_Exit(X = Parameters(NbSegments));

	Yt = ThicknessDistribution(X);

	TColGeom_Ary1dOfPnt3d UP(NbSegments + 1);
	TColGeom_Ary1dOfPnt3d LP(NbSegments + 1);

	forThose
	(
		Index,
		0,
		NbSegments
	)
	{
		UP[Index] = Geom_Pnt3d(X[Index], Yt[Index], 0) * theChord_;
		LP[Index] = Geom_Pnt3d(X[Index], -Yt[Index], 0) * theChord_;

	}

	Handle(TColgp_HArray1OfPnt) UP1 = new TColgp_HArray1OfPnt(1, UP.Size());
	forThose(Index, 0, MaxIndexOf(UP))
		UP1->SetValue(Index + 1, UP[Index]);

	Handle(TColgp_HArray1OfPnt) LP1 = new TColgp_HArray1OfPnt(1, LP.Size());
	forThose(Index, 0, MaxIndexOf(LP))
		LP1->SetValue(Index + 1, LP[Index]);

	GeomAPI_Interpolate Interpolation1(UP1, Standard_False, 1.0E-6);
	Interpolation1.Perform();

	GeomAPI_Interpolate Interpolation2(LP1, Standard_False, 1.0E-6);
	Interpolation2.Perform();

	theUpper_ = (Handle(Geom_BSplineCurve))Interpolation1.Curve();
	theLower_ = (Handle(Geom_BSplineCurve))Interpolation2.Curve();

	IsDone_ = Standard_True;
}

TColStd_Ary1dOfReal AutLib::CadLib::Rudder_Section::Parameters(const Standard_Integer NbSegmets) const
{
	if (NbSegmets < 1) THROW_STANDARD_EXCEPTION(" Invalid Nb of segments");

	TColStd_Ary1dOfReal X(NbSegmets + 1);
	const Standard_Real Dx = PI / (Standard_Real)NbSegmets;

	forThose(Index, 0, NbSegmets)
		X[Index] = 0.5*(1.0 - cos(Index*Dx));
	X.Last() = (1.0 - theTEGap_);
	MOVE(X);
}

TColStd_Ary1dOfReal AutLib::CadLib::Rudder_Section::ThicknessDistribution(const TColStd_Ary1dOfReal & Parameters) const
{
	const Standard_Integer NbSegmets = Parameters.Size();
	const Standard_Real Thickness = theThickness_ / 100.0;

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