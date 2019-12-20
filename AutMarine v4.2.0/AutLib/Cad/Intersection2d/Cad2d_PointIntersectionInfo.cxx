#include <Cad2d_PointIntersectionInfo.hxx>

#include <IO_Tecplot.hxx>

AutLib::CadLib::Cad2d_PointIntersectionInfo::Cad2d_PointIntersectionInfo()
{
}

AutLib::CadLib::Cad2d_PointIntersectionInfo::Cad2d_PointIntersectionInfo
(
	const Standard_Real theParameter1,
	const Standard_Real theParameter2,
	const Geom_Pnt2d & thePoint
)
	: theParameter1_(theParameter1)
	, theParameter2_(theParameter2)
	, thePoint_(thePoint)
{
}

void AutLib::CadLib::Cad2d_PointIntersectionInfo::Init
(
	const Standard_Real theParameter1, 
	const Standard_Real theParameter2, 
	const Geom_Pnt2d & thePoint
)
{
	theParameter1_ = theParameter1;
	theParameter2_ = theParameter2;

	thePoint_ = thePoint;
}

void AutLib::CadLib::Cad2d_PointIntersectionInfo::ExportToPlt(fstream & File) const
{
	M_IO IO_TecPlot::ExportPoint(thePoint_, File);
}