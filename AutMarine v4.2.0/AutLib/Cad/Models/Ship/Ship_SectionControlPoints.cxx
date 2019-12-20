#include <Ship_SectionControlPoints.hxx>

#include <Ship_ConstParameters.hxx>

using namespace AutLib;

AutLib::CadLib::Ship_SectionControlPoints::Ship_SectionControlPoints(Standard_Integer nbControlPoints)
	: nbControlPoints_(nbControlPoints)
{
	Try_Exception_Handle_Exit(AllocateMemory());
}

void AutLib::CadLib::Ship_SectionControlPoints::SetPoints(const TColGeom_Ary1dOfPnt3d & PointList)
{
	/*assert(!Is_Null_Vector(PointList));

	THROW_STANDARD_EXCEPTION_IF(PointList.size() != ControlPoints_.size(), " Conflict array sizes");*/

	ControlPoints_ = PointList;

	nbControlPoints_ = PointList.Size();
}

void AutLib::CadLib::Ship_SectionControlPoints::SetPoint
(
	Standard_Integer Index,
	const Geom_Pnt3d & Coord
)
{
	THROW_STANDARD_EXCEPTION_IF(Index < 0 || Index >= ControlPoints_.Size(), " Bad Subscript");

	Try_Exception_Handle_Exit(ControlPoints_[Index] = Coord);
}

void AutLib::CadLib::Ship_SectionControlPoints::SetCorner(Standard_Integer Index)
{
	IF_NOT_INSIDE
	(
		Index,
		0,
		Ship_ConstParameters::MaxNbRows() - 1
	)
	{
		THROW_STANDARD_EXCEPTION(" Invalid Corner Index");
	}

	CornerIndex_ = Index;
}

const TColGeom_Ary1dOfPnt3d & AutLib::CadLib::Ship_SectionControlPoints::ControlPoints() const
{
	return ControlPoints_;
}

TColGeom_Ary1dOfPnt3d & AutLib::CadLib::Ship_SectionControlPoints::ControlPoints()
{
	return ControlPoints_;
}

Standard_Integer AutLib::CadLib::Ship_SectionControlPoints::Corner() const
{
	return CornerIndex_;
}

Standard_Integer AutLib::CadLib::Ship_SectionControlPoints::NbPoints() const
{
	return nbControlPoints_;
}

#include <IO_TecPlot.hxx>

void AutLib::CadLib::Ship_SectionControlPoints::ExportToTecPlot(fstream & File) const
{
	IoLib::IO_TecPlot::ExportCurve
	(
		ControlPoints_,
		File
	);
}

void AutLib::CadLib::Ship_SectionControlPoints::AllocateMemory()
{
	Standard_Integer nbControlPoints = NbPoints();

	IF_NOT_INSIDE
	(
		nbControlPoints,
		Ship_ConstParameters::MinNbRows(),
		Ship_ConstParameters::MaxNbRows()
	)
	{
		THROW_STANDARD_EXCEPTION(" Invalid Number of control points");
	}

	ControlPoints_.Resize(nbControlPoints_);
	//ControlPoints_.Init(Geom_Pnt3d(0, 0, 0));
}