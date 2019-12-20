#include <Prop_BladeFaces.hxx>
#include <Prop_Propeller.hxx>

#include <Prop_WrappedSection.hxx>
#include <IO_Tecplot.hxx>

#include <Geom_BSplineSurface.hxx>
#include <GeomAPI_PointsToBSplineSurface.hxx>

AutLib::CadLib::Prop_BladeFaces::Prop_BladeFaces()
{
}

AutLib::CadLib::Prop_BladeFaces::Prop_BladeFaces
(
	const Handle(Geom_Surface)& theFace,
	const Handle(Geom_Surface)& theBack
)
	: theFace_(theFace)
	, theBack_(theBack)
{
}

void AutLib::CadLib::Prop_BladeFaces::Init
(
	const Handle(Geom_Surface)& theFace,
	const Handle(Geom_Surface)& theBack
)
{
	theFace_ = theFace;
	theBack_ = theBack;
}

void AutLib::CadLib::Prop_BladeFaces::SetFace(const Handle(Geom_Surface)& theFace)
{
	theFace_ = theFace;
}

void AutLib::CadLib::Prop_BladeFaces::SetBack(const Handle(Geom_Surface)& theBack)
{
	theBack_ = theBack;
}

void AutLib::CadLib::Prop_BladeFaces::ExportToPlt(fstream & File) const
{
	Handle(Geom_BSplineSurface) Surface = Handle(Geom_BSplineSurface)::DownCast(theFace_);
	Debug_Null_Pointer(Surface.IsNull());

	Standard_Real Umin = Surface->UKnot(Surface->FirstUKnotIndex());
	Standard_Real Umax = Surface->UKnot(Surface->LastUKnotIndex());
	Standard_Real Vmin = Surface->VKnot(Surface->FirstVKnotIndex());
	Standard_Real Vmax = Surface->VKnot(Surface->LastVKnotIndex());

	M_IO IO_TecPlot::ExportSurface(*theFace_, Umin, Umax, Vmin, Vmax, 80, 80, File);

	Surface = Handle(Geom_BSplineSurface)::DownCast(theBack_);
	Debug_Null_Pointer(Surface.IsNull());

	Umin = Surface->UKnot(Surface->FirstUKnotIndex());
	Umax = Surface->UKnot(Surface->LastUKnotIndex());
	Vmin = Surface->VKnot(Surface->FirstVKnotIndex());
	Vmax = Surface->VKnot(Surface->LastVKnotIndex());

	M_IO IO_TecPlot::ExportSurface(*theBack_, Umin, Umax, Vmin, Vmax, 80, 80, File);
}

void AutLib::CadLib::Prop_Propeller::CreateBladeFaces()
{
	Standard_Integer NbSections = theParameters_.NbSections();
	Standard_Integer NbSpans = theParameters_.NbSpans();

	Global_Handle(Prop_BladeFaces) BladeFaces = new Prop_BladeFaces;

	TColgp_Array2OfPnt Q(1, NbSections, 1, NbSpans);
	forThose
	(
		Index,
		0, 
		NbSections - 1
	)
	{
		Get_Const_Object(Wrapped) = *thePropView_.WrappedSection(Index);
		forThose(J, 0, NbSpans - 1)
		{
			Q.SetValue(Index + 1, J + 1, Wrapped.FaceOffset(J));
		}
	}

	GeomAPI_PointsToBSplineSurface Interpolation;
	Interpolation.Interpolate(Q);

	Debug_If_Condition_Message(NOT Interpolation.IsDone(), "interpolation is not performed");

	BladeFaces->SetFace(Interpolation.Surface());

	forThose
	(
		Index,
		0,
		NbSections - 1
	)
	{
		Get_Const_Object(Wrapped) = *thePropView_.WrappedSection(Index);
		forThose(J, 0, NbSpans - 1)
			Q.SetValue(Index + 1, J + 1, Wrapped.BackOffset(J));
	}

	Interpolation.Interpolate(Q);

	Debug_If_Condition_Message(NOT Interpolation.IsDone(), "interpolation is not performed");

	BladeFaces->SetBack(Interpolation.Surface());

	theBlades_.SetFirst(BladeFaces);
}