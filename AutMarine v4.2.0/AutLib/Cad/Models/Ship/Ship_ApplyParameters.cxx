#include <Ship_Hull.hxx>

#include <Geom_Pnt2d.hxx>
#include <Geom_Pnt3d.hxx>
#include <Geometry_Tools.hxx>
#include <Ship_SectionControlPoints.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace GeoLib;

#include <Geom2d_Curve.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>

void AutLib::CadLib::Ship_Hull::ApplyTightness()
{
	const Ship_Dimensions & Dimension = theParameters_.Dimensions();

	Get_Const_Object(Tightness) = theXParameters_.Tightness();

	Try_Exception_Handle_Exit
	(
		forThose
		(
			Section,
			0,
			Dimension.NbNetColumns() - 3
		)
	{
		ApplyTightness
		(
			*theSections_[Section],
			Tightness[Section]
		);
	}
	);
}

void AutLib::CadLib::Ship_Hull::ApplyFlare()
{
	const Ship_Dimensions & Dimension = theParameters_.Dimensions();

	const TColStd_Ary1dOfReal & Flare = theXParameters_.Flare();

	Try_Exception_Handle_Exit
	(
		forThose
		(
			Section,
			0,
			Dimension.NbNetColumns() - 3
		)
	{
		ApplyFlare(Section);
	}
	);
}

void AutLib::CadLib::Ship_Hull::ApplyRake()
{
	const Ship_Dimensions & Dimension = theParameters_.Dimensions();

	const TColStd_Ary1dOfReal & Rake = theXParameters_.Rake();

	Try_Exception_Handle_Exit
	(
		forThose
		(
			Section,
			0,
			Dimension.NbNetColumns() - 1
		)
	{
		ApplyRake
		(
			*theSections_[Section],
			Rake[Section]
		);
	}
	);
}

void AutLib::CadLib::Ship_Hull::ApplyForeFootShape()
{
	const Ship_Dimensions & Dimensions = theParameters_.Dimensions();

	const Ship_StemForm & Stem = theParameters_.Stem();

	Standard_Integer NbSections = Dimensions.NbNetColumns();

	TColGeom_Ary1dOfPnt3d & ControlPoints1 = (*theSections_[NbSections - 1]).ControlPoints();
	TColGeom_Ary1dOfPnt3d & ControlPoints3 = (*theSections_[NbSections - 3]).ControlPoints();

	Geom_Pnt3d Root = ControlPoints1[0];

	Geom_Pnt3d P1 = ControlPoints1[1];
	Geom_Pnt3d P2 = ControlPoints3[0];

	Geom_Pnt3d NewP1 = Root + Stem.ForeFootShape()*(P1 - Root);
	Geom_Pnt3d NewP2 = Root + Stem.ForeFootShape()*(P2 - Root);

	ControlPoints1[1] = NewP1;

	ControlPoints1[0] = MEAN
	(
		NewP1,
		NewP2
	);

	Standard_Real
		dx,
		dz,
		zMax;

	dx = NewP2.X() - ControlPoints3[0].X();

	zMax = ControlPoints3[ControlPoints3.Size() - 1].Z();

	forThose_Dec
	(
		Index,
		ControlPoints3.Size() - 2,
		0
	)
	{
		dz = zMax - ControlPoints3[Index].Z();

		ControlPoints3[Index].X() += (dz / zMax)*dx;
	}

	TColGeom_Ary1dOfPnt3d & ControlPoints2 = (*theSections_[NbSections - 2]).ControlPoints();

	Standard_Real y1 = ControlPoints2[1].Y();

	ControlPoints2[0] = ControlPoints1[0];
	ControlPoints2[1] = ControlPoints1[1];

	ControlPoints2[1].Y() = y1;
	ControlPoints2[0].Y() = MEAN(ControlPoints3[1].Y(), y1);
}

void AutLib::CadLib::Ship_Hull::ApplyParameters()
{
	CreateFlareProfile();

	ApplyTightness();

	Try_Exception_Handle_Exit(ApplyFlare());

	ApplyRake();

	ApplyForeFootShape();

	//ApplyBowSmoothness();
}

void AutLib::CadLib::Ship_Hull::ApplyTightness
(
	Ship_SectionControlPoints & Section,
	const Standard_Real Tightness
)
{
	Geom_Pnt3d
		crit_point1,
		crit_point2,
		new_pos1,
		new_pos2,
		p2;

	Standard_Real
		t,
		du,
		dv;

	Standard_Integer nbctrlpts = Section.NbPoints();

	Standard_Integer Corner = Section.Corner();

	Standard_Integer
		nx,
		ny;

	nx = Corner - 1;
	du = ONE / (Standard_Real)nx;

	ny = (nbctrlpts - 1) - Corner - 1;
	dv = ONE / (Standard_Real)ny;

	const TColGeom_Ary1dOfPnt3d & ControlPoints = Section.ControlPoints();

	if (Tightness <= (Standard_Real)0.5)
	{
		Try_Exception_Handle_Exit(crit_point1 = ControlPoints[1];);
		Try_Exception_Handle_Exit(crit_point2 = ControlPoints[nbctrlpts - 2];);

		Try_Exception_Handle_Exit(p2 = ControlPoints[Corner];);

		t = ONE - (Standard_Real)2.0*Tightness;

		new_pos1 = crit_point1 + t*(p2 - crit_point1);

		Try_Exception_Handle_Exit
		(
			forThose
			(
				Index,
				0,
				nx - 1
			)
		{
			Section.SetPoint(Index + 1, new_pos1 + Index*du*(p2 - new_pos1));
		}
		);

		new_pos2 = crit_point2 + t*(p2 - crit_point2);

		Try_Exception_Handle_Exit
		(
			forThose
			(
				Index,
				0,
				ny - 1
			)
		{
			Section.SetPoint(nbctrlpts - Index - 2, new_pos2 + Index*dv*(p2 - new_pos2));
		}
		);
	}
	else
	{
		Try_Exception_Handle_Exit(crit_point1 = ControlPoints[Corner - 1];);
		Try_Exception_Handle_Exit(crit_point2 = ControlPoints[Corner + 1];);

		Try_Exception_Handle_Exit(p2 = ControlPoints[0];);

		t = (Standard_Real)2.0*(Tightness - (Standard_Real)0.5);

		new_pos1 = crit_point1 + t*(p2 - crit_point1);

		Try_Exception_Handle_Exit
		(
			forThose
			(
				Index,
				0,
				nx - 1
			)
		{
			Section.SetPoint(Corner - Index - 1, new_pos1 + Index*du*(p2 - new_pos1));
		}
		);

		Try_Exception_Handle_Exit(p2 = ControlPoints[nbctrlpts - 1];);

		new_pos2 = crit_point2 + t*(p2 - crit_point2);

		Try_Exception_Handle_Exit
		(
			forThose
			(
				Index,
				0,
				ny - 1
			)
		{
			Section.SetPoint(Corner + Index + 1, new_pos2 + Index*dv*(p2 - new_pos2));
		}
		);
	}
}

void AutLib::CadLib::Ship_Hull::ApplyFlare(Standard_Integer Index)
{
	Global_Handle(Ship_SectionControlPoints) SectionPtr(0);

	Try_Exception_Handle_Exit(SectionPtr = theSections_[Index]);

	if (SectionPtr == NULL)
	{
		THROW_STANDARD_EXCEPTION(" Found no Section");
	}

	Ship_SectionControlPoints & Section = *SectionPtr;

	Standard_Integer Corner = Section.Corner();
	Standard_Integer NbPoints = Section.NbPoints();

	TColGeom_Ary1dOfPnt3d & CtrlPoints = Section.ControlPoints();

	if (theProfiles_.Flare(Index).IsNull())
	{
		THROW_STANDARD_EXCEPTION(" Found no Flare Profile");
	}

	Standard_Real zSection;
	Geom2dAPI_InterCurveCurve Intersection;

	forThose
	(
		J,
		Corner + 1,
		NbPoints - 2
	)
	{
		Try_Exception_Handle_Exit(zSection = CtrlPoints[J].Z());

		Handle(Geom2d_Line) Line = new Geom2d_Line(gp_Pnt2d(0, zSection), gp_Vec2d(1, 0));

		Intersection.Init(theProfiles_.Flare(Index), Line, 1.0e-6);

		if (NOT Intersection.NbPoints())
		{
			THROW_STANDARD_EXCEPTION(" No Intersection has been found");
		}

		if (Intersection.NbPoints() != 1)
		{
			THROW_STANDARD_EXCEPTION(" More than one intersection point has been found");
		}

		Geom_Pnt2d IP = Intersection.Point(1);

		Section.SetPoint
		(
			J,
			Geom_Pnt3d(CtrlPoints[J].X(), IP.X(), IP.Y())
		);
	}
}

void AutLib::CadLib::Ship_Hull::ApplyRake(Ship_SectionControlPoints & Section, const Standard_Real Rake)
{
	Standard_Integer NbPoints = Section.NbPoints();

	TColGeom_Ary1dOfPnt3d & ControlPoints = Section.ControlPoints();

	Standard_Real
		zSection,
		dx,
		dz;

	Try_Exception_Handle_Exit(zSection = ControlPoints[NbPoints - 1].Z(););

	dx = zSection*tan(Geometry_Tools::DegToRadian(Rake));

	Try_Exception_Handle_Exit
	(
		forThose_Dec
		(
			Row,
			NbPoints - 2,
			0
		)
	{
		dz = zSection - ControlPoints[Row].Z();

		ControlPoints[Row].X() -= (dz / zSection)*dx;
	}
	);
}