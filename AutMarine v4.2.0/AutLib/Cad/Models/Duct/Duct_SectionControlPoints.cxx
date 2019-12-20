#include <Duct_SectionControlPoints.hxx>

#include <IO_TecPlot.hxx>

AutLib::CadLib::Duct_SectionControlPoints::Duct_SectionControlPoints()
	: theControlPoints_(11)
{
}

void AutLib::CadLib::Duct_SectionControlPoints::SetPoints(const TColGeom_Ary1dOfPnt3d & thePointList)
{
	theControlPoints_ = thePointList;
}

void AutLib::CadLib::Duct_SectionControlPoints::SetPoint(const Standard_Integer theIndex, const Geom_Pnt3d & theCoord)
{
	Debug_Bad_Index_Array1(theIndex, theControlPoints_);
	theControlPoints_.SetValue(theIndex, theCoord);
}

void AutLib::CadLib::Duct_SectionControlPoints::ExportToTecPlot(fstream & File) const
{
	IoLib::IO_TecPlot::ExportCurve
	(
		theControlPoints_,
		File
	);
}