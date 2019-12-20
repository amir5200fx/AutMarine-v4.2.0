#include <Ship_Profiles.hxx>
#include <Ship_Hull.hxx>

#include <Ship_ConstParameters.hxx>
#include <Ship_SectionControlPoints.hxx>
#include <IO_Tecplot.hxx>

using namespace AutLib;
using namespace CadLib;

#include <Geom2d_BSplineCurve.hxx>
#include <TColgp_Array1OfPnt2d.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColStd_Array1OfInteger.hxx>

AutLib::CadLib::Ship_Profiles::Ship_Profiles()
{
}

void AutLib::CadLib::Ship_Profiles::SetMemory(const Standard_Integer nbSections)
{
	theFlare_.Resize(nbSections);
	theSkeg_.Resize(nbSections);
	theSection_.Resize(nbSections);
}

void AutLib::CadLib::Ship_Profiles::ExportFlareToTecPlot(fstream & File) const
{
	forThose(Index, 0, MaxIndexOf(theFlare_))
	{
		M_IO IO_TecPlot::ExportCurve(*theFlare_[Index], 0, 1, 40, File);
	}
}

void AutLib::CadLib::Ship_Profiles::ExportSkegToTecPlot(fstream & File) const
{
	forThose(Index, 0, MaxIndexOf(theSkeg_))
	{
		M_IO IO_TecPlot::ExportCurve(*theSkeg_[Index], 0, 1, 40, File);
	}
}

void AutLib::CadLib::Ship_Profiles::ExportSectionToTecPlot(fstream & File) const
{
	forThose(Index, 0, MaxIndexOf(theSection_))
	{
		M_IO IO_TecPlot::ExportCurve(*theSection_[Index], 0, 1, 40, File);
	}
}

void AutLib::CadLib::Ship_Profiles::ExportDeckToTecPlot(fstream & File) const
{
	M_IO IO_TecPlot::ExportCurve(*theDeck_, 0, 1, 40, File);
}

void AutLib::CadLib::Ship_Profiles::ExportButtockToTecPlot(fstream & File) const
{
	M_IO IO_TecPlot::ExportCurve(*theButtock_, 0, 1, 40, File);
}

void AutLib::CadLib::Ship_Hull::CreateDeckProfile()
{
	const Ship_Dimensions & Dimensions = theParameters_.Dimensions();
	const Ship_HullForm & Hull = theParameters_.Hull();
	const Ship_TransomForm & Transom = theParameters_.Transom();
	const Ship_StemForm & Stem = theParameters_.Stem();

	Standard_Real MinBowCoeff = Ship_ConstParameters::MinBowRounding();

	Standard_Integer nbPoles = 5;

	TColgp_Array1OfPnt2d Points(1, nbPoles);
	Points.SetValue(1, gp_Pnt2d(0, Transom.Width()*Dimensions.BeamOnDeck()));
	Points.SetValue(2, gp_Pnt2d(0, Dimensions.BeamOnDeck()));
	Points.SetValue(3, gp_Pnt2d(Hull.MaxAreaLocation()*Dimensions.LengthOnDeck(), Dimensions.BeamOnDeck()));
	Points.SetValue(4, gp_Pnt2d(Dimensions.LengthOnDeck(), Dimensions.BeamOnDeck()));
	Points.SetValue(5, gp_Pnt2d(Dimensions.LengthOnDeck(), Stem.BowRounding()*Dimensions.BeamOnDeck()));

	TColStd_Array1OfReal Weights(1, nbPoles);
	Weights.Init(1);

	Weights.SetValue(2, Hull.FullnessAft());
	Weights.SetValue(4, Hull.FullnessAft());

	Standard_Integer
		MaxIndex,
		Degree;

	MaxIndex = nbPoles - 1;
	Degree = 2;

	TColStd_Array1OfReal Knots(1, 3);
	TColStd_Array1OfInteger Mults(1, 3);

	Knots.SetValue(1, 0);
	Knots.SetValue(2, Hull.MaxAreaLocation());
	Knots.SetValue(3, 1);

	Mults.SetValue(1, 3);
	Mults.SetValue(2, 2);
	Mults.SetValue(3, 3);

	Handle(Geom2d_BSplineCurve) Deck = new Geom2d_BSplineCurve(Points, Weights, Knots, Mults, Degree);
	theProfiles_.SetDeck(Deck);
}

void AutLib::CadLib::Ship_Hull::CreateFlareProfile()
{
	forThose(Section, 0, theParameters_.Dimensions().NbNetColumns() - 3)
		Ship_Hull::CreateFlareProfile(Section);
}

void AutLib::CadLib::Ship_Hull::CreateFlareProfile(const Standard_Integer Index)
{
	Global_Handle(Ship_SectionControlPoints) SectionPtr(0);

	Try_Exception_Handle_Exit(SectionPtr = theSections_[Index]);

	Debug_Null_Pointer(SectionPtr);
	const Ship_SectionControlPoints & Section = *SectionPtr;

	Standard_Integer Corner = Section.Corner();
	Standard_Integer NbPoints = Section.NbPoints();

	Standard_Integer NbPoles = 3;

	TColgp_Array1OfPnt2d Poles(1, NbPoles);

	Get_Const_Object(CtrlPoints) = Section.ControlPoints();

	Poles.SetValue(1, gp_Pnt2d(CtrlPoints[Corner].Y(), CtrlPoints[Corner].Z()));
	Poles.SetValue(3, gp_Pnt2d(CtrlPoints[NbPoints - 1].Y(), CtrlPoints[NbPoints - 1].Z()));

	Poles.SetValue(2, gp_Pnt2d(Poles.Value(1).X(), Poles.Value(3).Y()));

	TColStd_Array1OfReal Weights(1, NbPoles);
	Weights.Init(1);
	Weights.SetValue(2, MAX(theXParameters_.Flare().Value(Index), 1.0e-6));

	Standard_Integer
		MaxIndex,
		Degree;

	MaxIndex = NbPoles - 1;
	Degree = 2;

	TColStd_Array1OfReal Knots(1, 2);
	Knots.SetValue(1, 0);
	Knots.SetValue(2, 1);

	TColStd_Array1OfInteger Mults(1, 2);
	Mults.SetValue(1, 3);
	Mults.SetValue(2, 3);

	Handle(Geom2d_BSplineCurve) FlareCurve = new Geom2d_BSplineCurve(Poles, Weights, Knots, Mults, Degree);
	theProfiles_.SetFlare(Index, FlareCurve);
}