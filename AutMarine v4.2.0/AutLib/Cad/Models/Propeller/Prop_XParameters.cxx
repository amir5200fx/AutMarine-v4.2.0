#include <Prop_XParameters.hxx>
#include <Prop_Propeller.hxx>

#include <Geometry_Tools.hxx>

using namespace AutLib;
using namespace GeoLib;

#include <Geom2d_Line.hxx>
#include <Geom2d_Curve.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>

AutLib::CadLib::Prop_XParameters::Prop_XParameters()
{
}

AutLib::CadLib::Prop_XParameters::Prop_XParameters(const Standard_Integer theNbSegments)
	: theX_(theNbSegments)
	, thePitchAngle_(theNbSegments)
	, theChord_(theNbSegments)
	, theMaxCamber_(theNbSegments)
	, theMaxCamberPosition_(theNbSegments)
	, theSkew_(theNbSegments)
	, theRake_(theNbSegments)
	, theThickness_(theNbSegments)
{
	theX_.Init(ZERO);
	thePitchAngle_.Init(ZERO);
	theChord_.Init(ZERO);
	theMaxCamber_.Init(ZERO);
	theMaxCamberPosition_.Init(ZERO);
	theSkew_.Init(ZERO);
	theRake_.Init(ZERO);
	theThickness_.Init(ZERO);
}

void AutLib::CadLib::Prop_XParameters::AllocateMemory(const Standard_Integer theNbSegments)
{
	theX_.Resize(theNbSegments);

	thePitchAngle_.Resize(theNbSegments);
	theChord_.Resize(theNbSegments);
	theMaxCamber_.Resize(theNbSegments);
	theMaxCamberPosition_.Resize(theNbSegments);
	theSkew_.Resize(theNbSegments);
	theRake_.Resize(theNbSegments);
	theThickness_.Resize(theNbSegments);

	theX_.Init(ZERO);

	thePitchAngle_.Init(ZERO);
	theChord_.Init(ZERO);
	theMaxCamber_.Init(ZERO);
	theMaxCamberPosition_.Init(ZERO);
	theSkew_.Init(ZERO);
	theRake_.Init(ZERO);
	theThickness_.Init(ZERO);
}

void AutLib::CadLib::Prop_Propeller::CalcXSections()
{
	Get_Const_Object(Parameters) = theParameters_;
	Standard_Integer NbSections = theParameters_.NbSections();

	Standard_Real TipRadius = (Parameters.Diameter() / 2 - Parameters.TipGap()*(Parameters.Diameter() / 2));
	Standard_Real dx = (TipRadius - Parameters.HubRadius()) / (Standard_Real)(NbSections - 1);

	forThose(Index, 0, NbSections - 1)
		theXParameters_.SetX(Index, Index*dx + Parameters.HubRadius());
}

void AutLib::CadLib::Prop_Propeller::CalcXPitch()
{
	Standard_Integer NbSections = theParameters_.NbSections();

	Debug_Null_Pointer(theProfiles_.PitchProfile());

	Get_Const_Object(Curve) = *theProfiles_.PitchProfile();

	Geom_Pnt2d P0 = Curve.Value(Curve.FirstParameter());
	Geom_Pnt2d Pn = Curve.Value(Curve.LastParameter());
	
	theXParameters_.SetPitchAngle(0, Geometry_Tools::DegToRadian(P0.Y()));

	Geom_Pnt2d Point;
	Geom2dAPI_InterCurveCurve Intersection;
	forThose
	(
		Index,
		1, 
		NbSections
	)
	{
		Standard_Real xSection = theXParameters_.X(Index_Of(Index));
		
		Handle(Geom2d_Line) Line = new Geom2d_Line(gp_Pnt2d(xSection, 0), gp_Dir2d(0, 1));

		Intersection.Init(theProfiles_.PitchProfile(), Line, 1.0e-6);

		if (NOT Intersection.NbPoints())
		{
			THROW_STANDARD_EXCEPTION(" No Intersection has been found");
		}

		if (Intersection.NbPoints() != 1)
		{
			THROW_STANDARD_EXCEPTION(" More than one intersection point has been found");
		}

		Point = Intersection.Point(1);

		theXParameters_.SetPitchAngle(Index_Of(Index), Geometry_Tools::DegToRadian(Point.Y()));
	}
}

void AutLib::CadLib::Prop_Propeller::CalcXSkew()
{
	Standard_Integer NbSections = theParameters_.NbSections();

	Debug_Null_Pointer(theProfiles_.SkewProfile());

	Get_Const_Object(Curve) = *theProfiles_.SkewProfile();

	Geom_Pnt2d P0 = Curve.Value(Curve.FirstParameter());
	Geom_Pnt2d Pn = Curve.Value(Curve.LastParameter());

	theXParameters_.SetSkew(0, P0.Y());

	Geom_Pnt2d Point;
	Geom2dAPI_InterCurveCurve Intersection;
	forThose
	(
		Index,
		1,
		NbSections
	)
	{
		Standard_Real xSection = theXParameters_.X(Index_Of(Index));

		Handle(Geom2d_Line) Line = new Geom2d_Line(gp_Pnt2d(xSection, 0), gp_Dir2d(0, 1));

		Intersection.Init(theProfiles_.SkewProfile(), Line, 1.0e-6);

		if (NOT Intersection.NbPoints())
		{
			THROW_STANDARD_EXCEPTION(" No Intersection has been found");
		}

		if (Intersection.NbPoints() != 1)
		{
			THROW_STANDARD_EXCEPTION(" More than one intersection point has been found");
		}

		Point = Intersection.Point(1);

		theXParameters_.SetSkew(Index_Of(Index), Point.Y());
	}
}

void AutLib::CadLib::Prop_Propeller::CalcXChord()
{
	Standard_Integer NbSections = theParameters_.NbSections();

	Debug_Null_Pointer(theProfiles_.ChordProfile());

	Get_Const_Object(Curve) = *theProfiles_.ChordProfile();

	Geom_Pnt2d P0 = Curve.Value(Curve.FirstParameter());
	Geom_Pnt2d Pn = Curve.Value(Curve.LastParameter());

	theXParameters_.SetChord(0, P0.Y());

	Geom_Pnt2d Point;
	Geom2dAPI_InterCurveCurve Intersection;
	forThose
	(
		Index,
		1,
		NbSections
	)
	{
		Standard_Real xSection = theXParameters_.X(Index_Of(Index));

		Handle(Geom2d_Line) Line = new Geom2d_Line(gp_Pnt2d(xSection, 0), gp_Dir2d(0, 1));

		Intersection.Init(theProfiles_.ChordProfile(), Line, 1.0e-6);

		if (NOT Intersection.NbPoints())
		{
			THROW_STANDARD_EXCEPTION(" No Intersection has been found");
		}

		if (Intersection.NbPoints() != 1)
		{
			THROW_STANDARD_EXCEPTION(" More than one intersection point has been found");
		}

		Point = Intersection.Point(1);

		theXParameters_.SetChord(Index_Of(Index), Point.Y());
	}
}

void AutLib::CadLib::Prop_Propeller::CalcXCamber()
{
	Standard_Integer NbSections = theParameters_.NbSections();

	Debug_Null_Pointer(theProfiles_.CamberProfile());

	Get_Const_Object(Curve) = *theProfiles_.CamberProfile();

	Geom_Pnt2d P0 = Curve.Value(Curve.FirstParameter());
	Geom_Pnt2d Pn = Curve.Value(Curve.LastParameter());

	theXParameters_.SetMaxCamber(0, P0.Y());
	theXParameters_.SetMaxCamberPosition(0, 0.4);

	Geom_Pnt2d Point;
	Geom2dAPI_InterCurveCurve Intersection;
	forThose
	(
		Index,
		1,
		NbSections
	)
	{
		Standard_Real xSection = theXParameters_.X(Index_Of(Index));

		Handle(Geom2d_Line) Line = new Geom2d_Line(gp_Pnt2d(xSection, 0), gp_Dir2d(0, 1));

		Intersection.Init(theProfiles_.CamberProfile(), Line, 1.0e-6);

		if (NOT Intersection.NbPoints())
		{
			THROW_STANDARD_EXCEPTION(" No Intersection has been found");
		}

		if (Intersection.NbPoints() != 1)
		{
			THROW_STANDARD_EXCEPTION(" More than one intersection point has been found");
		}

		Point = Intersection.Point(1);

		theXParameters_.SetMaxCamber(Index_Of(Index), Point.Y());
		theXParameters_.SetMaxCamberPosition(Index_Of(Index), 0.4);
	}
}

void AutLib::CadLib::Prop_Propeller::CalcXThickness()
{
	Standard_Integer NbSections = theParameters_.NbSections();

	Debug_Null_Pointer(theProfiles_.ThicknessProfile());

	Get_Const_Object(Curve) = *theProfiles_.ThicknessProfile();

	Geom_Pnt2d P0 = Curve.Value(Curve.FirstParameter());
	Geom_Pnt2d Pn = Curve.Value(Curve.LastParameter());

	theXParameters_.SetThickness(0, P0.Y());

	Geom_Pnt2d Point;
	Geom2dAPI_InterCurveCurve Intersection;
	forThose
	(
		Index,
		1,
		NbSections
	)
	{
		Standard_Real xSection = theXParameters_.X(Index_Of(Index));

		Handle(Geom2d_Line) Line = new Geom2d_Line(gp_Pnt2d(xSection, 0), gp_Dir2d(0, 1));

		Intersection.Init(theProfiles_.ThicknessProfile(), Line, 1.0e-6);

		if (NOT Intersection.NbPoints())
		{
			THROW_STANDARD_EXCEPTION(" No Intersection has been found");
		}

		if (Intersection.NbPoints() != 1)
		{
			THROW_STANDARD_EXCEPTION(" More than one intersection point has been found");
		}

		Point = Intersection.Point(1);

		theXParameters_.SetThickness(Index_Of(Index), Point.Y());
	}
}

void AutLib::CadLib::Prop_Propeller::CalcXRake()
{
	Standard_Integer NbSections = theParameters_.NbSections();

	Debug_Null_Pointer(theProfiles_.RakeProfile());

	Get_Const_Object(Curve) = *theProfiles_.RakeProfile();

	Geom_Pnt2d P0 = Curve.Value(Curve.FirstParameter());
	Geom_Pnt2d Pn = Curve.Value(Curve.LastParameter());

	theXParameters_.SetRake(0, P0.Y());

	Geom_Pnt2d Point;
	Geom2dAPI_InterCurveCurve Intersection;
	forThose
	(
		Index,
		1,
		NbSections
	)
	{
		Standard_Real xSection = theXParameters_.X(Index_Of(Index));

		Handle(Geom2d_Line) Line = new Geom2d_Line(gp_Pnt2d(xSection, 0), gp_Dir2d(0, 1));

		Intersection.Init(theProfiles_.RakeProfile(), Line, 1.0e-6);

		if (NOT Intersection.NbPoints())
		{
			THROW_STANDARD_EXCEPTION(" No Intersection has been found");
		}

		if (Intersection.NbPoints() != 1)
		{
			THROW_STANDARD_EXCEPTION(" More than one intersection point has been found");
		}

		Point = Intersection.Point(1);

		theXParameters_.SetRake(Index_Of(Index), Point.Y());
	}
}

void AutLib::CadLib::Prop_Propeller::CalcXParameters()
{
	CalcXSections();

	CalcXPitch();

	CalcXSkew();

	CalcXChord();

	CalcXCamber();

	CalcXThickness();

	CalcXRake();
}