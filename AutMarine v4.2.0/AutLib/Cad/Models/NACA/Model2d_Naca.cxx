#include <Model2d_Naca.hxx>

#include <IO_Tecplot.hxx>
#include <Geom2d_Curve.hxx>

AutLib::CadLib::Model2d_Naca::Model2d_Naca()
{
}

void AutLib::CadLib::Model2d_Naca::ExportToPlt(fstream & File) const
{
	M_IO IO_TecPlot::ExportCurve(*theUpper_, theUpper_->FirstParameter(), theUpper_->LastParameter(), 40, File);
	M_IO IO_TecPlot::ExportCurve(*theLower_, theLower_->FirstParameter(), theLower_->LastParameter(), 40, File);
}