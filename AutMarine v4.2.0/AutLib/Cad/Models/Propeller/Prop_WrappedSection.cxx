#include <Prop_WrappedSection.hxx>
#include <Prop_Propeller.hxx>

#include <Prop_ExpandedView.hxx>

#include <IO_Tecplot.hxx>

AutLib::CadLib::Prop_WrappedSection::Prop_WrappedSection(const Standard_Integer theNbPts)
	: theBack_(theNbPts)
	, theFace_(theNbPts)
{
}

void AutLib::CadLib::Prop_WrappedSection::ExportToPlt(fstream & File) const
{
	M_IO IO_TecPlot::ExportCurve(theFace_, File);
	M_IO IO_TecPlot::ExportCurve(theBack_, File);
}

void AutLib::CadLib::Prop_Propeller::CreateWrappedView()
{
	Standard_Integer NbSections = theParameters_.NbSections();
	Geom_Pnt3d Point;
	Standard_Real Omega;

	forThose
	(
		Section,
		0,
		NbSections - 1
	)
	{
		Standard_Real SK = theXParameters_.xSkew(Section);
		Standard_Real RK =  theXParameters_.xRake(Section);
		Standard_Real Pitch = theXParameters_.xPitchAngle(Section);
		Standard_Real Chord = theXParameters_.xChord(Section);

		Global_Handle(Prop_WrappedSection) WrappedSection = new Prop_WrappedSection(theParameters_.NbSpans());
		Get_Object(Wrapped) = *WrappedSection;

		forThose
		(
			Index,
			0,
			theParameters_.NbSpans() - 1
		)
		{
			Standard_Real Xs = thePropView_.ExpandedView(Section)->XS(Index);
			Standard_Real Tb = thePropView_.ExpandedView(Section)->TB(Index);
			Standard_Real Tf = thePropView_.ExpandedView(Section)->TF(Index);

			Point.Z() = SK*sin(Pitch) + Tb*cos(Pitch) - Xs*sin(Pitch);

			Omega = -(-SK*cos(Pitch) + Xs*cos(Pitch) + Tb*sin(Pitch)) / theXParameters_.X(Section);
			
			Point.X() = -theXParameters_.X(Section) * sin(Omega);
			Point.Y() = theXParameters_.X(Section) * cos(Omega);

			Wrapped.SetBackOffset(Index, Point);

			Point.Z() = SK*sin(Pitch) + Tf*cos(Pitch) - Xs*sin(Pitch);

			Omega = -(-SK*cos(Pitch) + Xs*cos(Pitch) + Tf*sin(Pitch)) / theXParameters_.X(Section);

			Point.X() = -theXParameters_.X(Section) * sin(Omega);
			Point.Y() = theXParameters_.X(Section) * cos(Omega);

			Wrapped.SetFaceOffset(Index, Point);
		}

		thePropView_.SetWrappedSection(Section, WrappedSection);
	}
}