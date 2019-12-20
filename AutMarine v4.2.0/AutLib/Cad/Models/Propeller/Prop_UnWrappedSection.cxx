#include <Prop_UnWrappedSection.hxx>
#include <Prop_Propeller.hxx>

#include <Prop_ExpandedView.hxx>
#include <IO_Tecplot.hxx>

AutLib::CadLib::Prop_UnWrappedSection::Prop_UnWrappedSection(const Standard_Integer theNbPts)
	: theBack_(theNbPts)
	, theFace_(theNbPts)
{
}

void AutLib::CadLib::Prop_UnWrappedSection::ExportToPlt(fstream & File) const
{
	M_IO IO_TecPlot::ExportCurve(theFace_, File);
	M_IO IO_TecPlot::ExportCurve(theBack_, File);
}

void AutLib::CadLib::Prop_Propeller::CreateUnWrappedView()
{
	Standard_Integer NbSections = theParameters_.NbSections();

	forThose
	(
		Section, 
		0,
		NbSections - 1
	)
	{
		Standard_Real SK = theXParameters_.xSkew(Section);
		Standard_Real RK = theXParameters_.xRake(Section);
		Standard_Real Pitch = theXParameters_.xPitchAngle(Section);
		Standard_Real Chord = theXParameters_.xChord(Section);

		Global_Handle(Prop_UnWrappedSection) UnWrappedSection = new Prop_UnWrappedSection(theParameters_.NbSpans());
		Get_Object(UnWrapped) = *UnWrappedSection;

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

			UnWrapped.SetBackOffset(Index, Geom_Pnt3d(SK*cos(Pitch) + Xs*cos(Pitch) - Tb*sin(Pitch), theXParameters_.X(Section), SK*sin(Pitch) + RK - Xs*sin(Pitch) - Tb*cos(Pitch)));
			UnWrapped.SetFaceOffset(Index, Geom_Pnt3d(SK*cos(Pitch) + Xs*cos(Pitch) - Tf*sin(Pitch), theXParameters_.X(Section), SK*sin(Pitch) + RK - Xs*sin(Pitch) - Tf*cos(Pitch)));
		}

		thePropView_.SetUnWrappedSection(Section, UnWrappedSection);
	}
}