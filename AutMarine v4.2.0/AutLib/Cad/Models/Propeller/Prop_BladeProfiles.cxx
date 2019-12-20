#include <Prop_BladeProfiles.hxx>
#include <Prop_Propeller.hxx>

#include <Geometry_Intersect.hxx>
#include <IO_Tecplot.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace IoLib;
using namespace GeoLib;

#include <Geom2d_BSplineCurve.hxx>

AutLib::CadLib::Prop_BladeProfiles::Prop_BladeProfiles()
	: thePitch_(NULL)
	, theChord_(NULL)
	, theCamber_(NULL)
	, theSkew_(NULL)
	, theRake_(NULL)
	, theThickness_(NULL)
{
}

void AutLib::CadLib::Prop_BladeProfiles::SetPitchProfile(const Prop_ParameterProfile & theProfile)
{
	thePitch_ = theProfile;
}

void AutLib::CadLib::Prop_BladeProfiles::SetChordProfile(const Prop_ParameterProfile & theProfile)
{
	theChord_ = theProfile;
}

void AutLib::CadLib::Prop_BladeProfiles::SetCamberProfile(const Prop_ParameterProfile & theProfile)
{
	theCamber_ = theProfile;
}

void AutLib::CadLib::Prop_BladeProfiles::SetSkewProfile(const Prop_ParameterProfile & theProfile)
{
	theSkew_ = theProfile;
}

void AutLib::CadLib::Prop_BladeProfiles::SetRakeProfile(const Prop_ParameterProfile & theProfile)
{
	theRake_ = theProfile;
}

void AutLib::CadLib::Prop_BladeProfiles::SetThicknessProfile(const Prop_ParameterProfile & theProfile)
{
	theThickness_ = theProfile;
}

void AutLib::CadLib::Prop_BladeProfiles::ExportPitchProfileToPlt(fstream & File) const
{
	Handle(Geom2d_BSplineCurve) Curve = Handle(Geom2d_BSplineCurve)::DownCast(thePitch_);
	Debug_Null_Pointer(Curve);

	IO_TecPlot::ExportCurve(*Curve, Curve->FirstParameter(), Curve->LastParameter(), 80, File);
}

void AutLib::CadLib::Prop_BladeProfiles::ExportChordProfileToPlt(fstream & File) const
{
	Handle(Geom2d_BSplineCurve) Curve = Handle(Geom2d_BSplineCurve)::DownCast(theChord_);
	Debug_Null_Pointer(Curve);

	IO_TecPlot::ExportCurve(*Curve, Curve->FirstParameter(), Curve->LastParameter(), 80, File);
}

void AutLib::CadLib::Prop_BladeProfiles::ExportCamberProfileToPlt(fstream & File) const
{
	Handle(Geom2d_BSplineCurve) Curve = Handle(Geom2d_BSplineCurve)::DownCast(theCamber_);
	Debug_Null_Pointer(Curve);

	IO_TecPlot::ExportCurve(*Curve, Curve->FirstParameter(), Curve->LastParameter(), 80, File);
}

void AutLib::CadLib::Prop_BladeProfiles::ExportSkewProfileToPlt(fstream & File) const
{
	Handle(Geom2d_BSplineCurve) Curve = Handle(Geom2d_BSplineCurve)::DownCast(theSkew_);
	Debug_Null_Pointer(Curve);

	IO_TecPlot::ExportCurve(*Curve, Curve->FirstParameter(), Curve->LastParameter(), 80, File);
}

void AutLib::CadLib::Prop_BladeProfiles::ExportRakeProfileToPlt(fstream & File) const
{
	Handle(Geom2d_BSplineCurve) Curve = Handle(Geom2d_BSplineCurve)::DownCast(theRake_);
	Debug_Null_Pointer(Curve);

	IO_TecPlot::ExportCurve(*Curve, Curve->FirstParameter(), Curve->LastParameter(), 80, File);
}

void AutLib::CadLib::Prop_BladeProfiles::ExportThicknessProfileToPlt(fstream & File) const
{
	Handle(Geom2d_BSplineCurve) Curve = Handle(Geom2d_BSplineCurve)::DownCast(theThickness_);
	Debug_Null_Pointer(Curve);

	IO_TecPlot::ExportCurve(*Curve, Curve->FirstParameter(), Curve->LastParameter(), 80, File);
}

void AutLib::CadLib::Prop_Propeller::CreatePitchProfile()
{
	Get_Const_Object(Parameters) = theParameters_;

	Geom_Pnt2d P0, P1, P2;

	P0.SetCoord(Parameters.HubRadius(), Parameters.BladeParameters().PitchForm().RootPitch());
	P2.SetCoord(Parameters.Diameter() / 2, Parameters.BladeParameters().PitchForm().TipPitch());

	Geom_Pnt2d t0, t2;
	Standard_Real dx = ABS(P2.X() - P0.X());
	Standard_Real dy = ABS(P2.Y() - P0.Y());

	Standard_Real theta0 = Parameters.BladeParameters().PitchForm().RootSteep()*(atan(dx / dy));
	Standard_Real theta2 = Parameters.BladeParameters().PitchForm().TipSteep()*(atan(dy / dx));

	t0.X() = sin(theta0);
	t0.Y() = -cos(theta0);

	t2.X() = -cos(theta2);
	t2.Y() = sin(theta2);

	if (ABS(CrossProduct(t0, t2)) < EPS6)
	{
		P1 = (P0 + P2) / 2;
	}
	else
	{
		P1 = Geometry_Intersect::IntersectionTwoLines(P0, t0, P2, t2);
	}

	Standard_Integer NbPoles = 3;
	Standard_Integer Degree = 2;

	TColgp_Array1OfPnt2d Poles(1, NbPoles);
	Poles.SetValue(1, P0);
	Poles.SetValue(2, P1);
	Poles.SetValue(3, P2);

	TColStd_Array1OfReal Weights(1, NbPoles);
	Weights.Init(1);

	TColStd_Array1OfReal Knots(1, 2);
	Knots.SetValue(1, 0);
	Knots.SetValue(2, 1);

	TColStd_Array1OfInteger Mults(1, 2);
	Mults.SetValue(1, 3);
	Mults.SetValue(2, 3);

	Prop_ParameterProfile Curve = new Geom2d_BSplineCurve(Poles, Weights, Knots, Mults, Degree);
	theProfiles_.SetPitchProfile(Curve);
}

void AutLib::CadLib::Prop_Propeller::CreateChordProfile()
{
	Get_Const_Object(Parameters) = theParameters_;

	Geom_Pnt2d P0, P1, P2, P3, P4;

	P0.SetCoord(Parameters.HubRadius(), Parameters.BladeParameters().ChordForm().RootChord());
	P1.SetCoord(P0.X(), Parameters.BladeParameters().ChordForm().MaxChord());
	P2.SetCoord(Parameters.BladeParameters().ChordForm().MaxChordLocation()*(Parameters.Diameter() / 2 - Parameters.HubRadius()) + Parameters.HubRadius(), Parameters.BladeParameters().ChordForm().MaxChord());
	P3.SetCoord(Parameters.Diameter() / 2, P2.Y());
	P4.SetCoord(P3.X(), Parameters.BladeParameters().ChordForm().TipChord());

	P1 = P1 + Parameters.BladeParameters().ChordForm().RootWeight()*(P2 - P1);

	Standard_Integer NbPoles = 5;
	Standard_Integer Degree = 2;

	TColgp_Array1OfPnt2d Poles(1, NbPoles);
	Poles.SetValue(1, P0);
	Poles.SetValue(2, P1);
	Poles.SetValue(3, P2);
	Poles.SetValue(4, P3);
	Poles.SetValue(5, P4);

	TColStd_Array1OfReal Weights(1, NbPoles);
	Weights.Init(1);
	//Weights.SetValue(2, Parameters.BladeParameters().ChordForm().RootWeight());
	Weights.SetValue(4, Parameters.BladeParameters().ChordForm().TipWeight());

	TColStd_Array1OfReal Knots(1, 3);
	Knots.SetValue(1, 0);
	Knots.SetValue(2, 0.5);
	Knots.SetValue(3, 1);

	TColStd_Array1OfInteger Mults(1, 3);
	Mults.SetValue(1, 3);
	Mults.SetValue(2, 2);
	Mults.SetValue(3, 3);

	Prop_ParameterProfile Curve = new Geom2d_BSplineCurve(Poles, Weights, Knots, Mults, Degree);
	theProfiles_.SetChordProfile(Curve);
}

void AutLib::CadLib::Prop_Propeller::CreateSkewProfile()
{
	Get_Const_Object(Parameters) = theParameters_;

	Geom_Pnt2d P0, P1, P2;

	P0.SetX(Parameters.HubRadius());
	P2.SetCoord(Parameters.Diameter() / 2, Parameters.BladeParameters().SkewForm().TipSkew());

	Geom_Pnt2d t0, t2;
	Standard_Real dx = ABS(P2.X() - P0.X());
	Standard_Real dy = ABS(P2.Y() - P0.Y());

	Standard_Real MaxTheta0 = atan(dy / dx);
	Standard_Real MinTheta0 = -0.5*MaxTheta0;

	Standard_Real theta0 = MinTheta0 + Parameters.BladeParameters().SkewForm().RootSteep()*(MaxTheta0 - MinTheta0);
	Standard_Real theta2 = Parameters.BladeParameters().SkewForm().TipSteep()*(atan(dx / dy));

	t0.X() = cos(theta0);
	t0.Y() = sin(theta0);

	t2.X() = -sin(theta2);
	t2.Y() = -cos(theta2);

	if (ABS(CrossProduct(t0, t2)) < EPS6)
	{
		P1 = (P0 + P2) / 2;
	}
	else
	{
		P1 = Geometry_Intersect::IntersectionTwoLines(P0, t0, P2, t2);
	}

	Standard_Integer NbPoles = 3;
	Standard_Integer Degree = 2;

	TColgp_Array1OfPnt2d Poles(1, NbPoles);
	Poles.SetValue(1, P0);
	Poles.SetValue(2, P1);
	Poles.SetValue(3, P2);

	TColStd_Array1OfReal Weights(1, NbPoles);
	Weights.Init(1);

	TColStd_Array1OfReal Knots(1, 2);
	Knots.SetValue(1, 0);
	Knots.SetValue(2, 1);

	TColStd_Array1OfInteger Mults(1, 2);
	Mults.SetValue(1, 3);
	Mults.SetValue(2, 3);

	Prop_ParameterProfile Curve = new Geom2d_BSplineCurve(Poles, Weights, Knots, Mults, Degree);
	theProfiles_.SetSkewProfile(Curve);
}

void AutLib::CadLib::Prop_Propeller::CreateCamberProfile()
{
	Get_Const_Object(Parameters) = theParameters_;

	Geom_Pnt2d P0, P1, P2, P3, P4;

	P0.SetCoord(Parameters.HubRadius(), Parameters.BladeParameters().CamberForm().RootCamber());
	P1.SetCoord(P0.X(), Parameters.BladeParameters().CamberForm().MaxCamber());
	P2.SetCoord(Parameters.BladeParameters().CamberForm().MaxCamberLocation()*(Parameters.Diameter() / 2 - Parameters.HubRadius()) + Parameters.HubRadius(), P1.Y());
	P3.SetCoord(Parameters.Diameter() / 2, P2.Y());
	P4.SetCoord(P3.X(), Parameters.BladeParameters().CamberForm().TipCamber());

	P1 = P1 + Parameters.BladeParameters().CamberForm().RootWeight()*(P2 - P1);

	Standard_Integer NbPoles = 5;
	Standard_Integer Degree = 2;

	TColgp_Array1OfPnt2d Poles(1, NbPoles);
	Poles.SetValue(1, P0);
	Poles.SetValue(2, P1);
	Poles.SetValue(3, P2);
	Poles.SetValue(4, P3);
	Poles.SetValue(5, P4);

	TColStd_Array1OfReal Weights(1, NbPoles);
	Weights.Init(1);
	//Weights.SetValue(2, Parameters.BladeParameters().CamberForm().RootWeight());
	Weights.SetValue(4, Parameters.BladeParameters().CamberForm().TipWeight());

	TColStd_Array1OfReal Knots(1, 3);
	Knots.SetValue(1, 0);
	Knots.SetValue(2, 0.5);
	Knots.SetValue(3, 1);

	TColStd_Array1OfInteger Mults(1, 3);
	Mults.SetValue(1, 3);
	Mults.SetValue(2, 2);
	Mults.SetValue(3, 3);

	Prop_ParameterProfile Curve = new Geom2d_BSplineCurve(Poles, Weights, Knots, Mults, Degree);
	theProfiles_.SetCamberProfile(Curve);
}

void AutLib::CadLib::Prop_Propeller::CreateThicknessProfile()
{
	Get_Const_Object(Parameters) = theParameters_;

	Geom_Pnt2d P0, P1, P2;

	P0.SetCoord(Parameters.HubRadius(), Parameters.BladeParameters().ThicknessForm().RootThickness());
	P2.SetCoord(Parameters.Diameter() / 2, Parameters.BladeParameters().ThicknessForm().TipThickness());

	Geom_Pnt2d t0, t2;
	Standard_Real dx = ABS(P2.X() - P0.X());
	Standard_Real dy = ABS(P2.Y() - P0.Y());

	Standard_Real theta0 = Parameters.BladeParameters().ThicknessForm().RootSteep()*(atan(dx / dy));
	Standard_Real theta2 = Parameters.BladeParameters().ThicknessForm().TipSteep()*(atan(dy / dx));

	t0.X() = sin(theta0);
	t0.Y() = -cos(theta0);

	t2.X() = -cos(theta2);
	t2.Y() = sin(theta2);

	if (ABS(CrossProduct(t0, t2)) < EPS6)
	{
		P1 = (P0 + P2) / 2;
	}
	else
	{
		P1 = Geometry_Intersect::IntersectionTwoLines(P0, t0, P2, t2);
	}

	Standard_Integer NbPoles = 3;
	Standard_Integer Degree = 2;

	TColgp_Array1OfPnt2d Poles(1, NbPoles);
	Poles.SetValue(1, P0);
	Poles.SetValue(2, P1);
	Poles.SetValue(3, P2);

	TColStd_Array1OfReal Weights(1, NbPoles);
	Weights.Init(1);

	TColStd_Array1OfReal Knots(1, 2);
	Knots.SetValue(1, 0);
	Knots.SetValue(2, 1);

	TColStd_Array1OfInteger Mults(1, 2);
	Mults.SetValue(1, 3);
	Mults.SetValue(2, 3);

	Prop_ParameterProfile Curve = new Geom2d_BSplineCurve(Poles, Weights, Knots, Mults, Degree);
	theProfiles_.SetThicknessProfile(Curve);
}

void AutLib::CadLib::Prop_Propeller::CreateRakeProfile()
{
	Get_Const_Object(Parameters) = theParameters_;

	Geom_Pnt2d P0, P1;
	P1.SetCoord(Parameters.Diameter() / 2, Parameters.BladeParameters().RakeForm().TipRake());

	Standard_Integer NbPoles = 2;
	Standard_Integer Degree = 1;

	TColgp_Array1OfPnt2d Poles(1, NbPoles);
	Poles.SetValue(1, P0);
	Poles.SetValue(2, P1);

	TColStd_Array1OfReal Weights(1, NbPoles);
	Weights.Init(1);

	TColStd_Array1OfReal Knots(1, 2);
	Knots.SetValue(1, 0);
	Knots.SetValue(2, 1);

	TColStd_Array1OfInteger Mults(1, 2);
	Mults.SetValue(1, 2);
	Mults.SetValue(2, 2);

	Prop_ParameterProfile Curve = new Geom2d_BSplineCurve(Poles, Weights, Knots, Mults, Degree);
	theProfiles_.SetRakeProfile(Curve);
}

void AutLib::CadLib::Prop_Propeller::CreateProfiles()
{
	CreatePitchProfile();

	CreateSkewProfile();

	CreateChordProfile();

	CreateCamberProfile();

	CreateThicknessProfile();

	CreateRakeProfile();
}