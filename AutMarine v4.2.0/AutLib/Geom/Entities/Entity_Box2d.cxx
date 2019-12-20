#include <Entity_Box2d.hxx>

#include <IO_Tecplot.hxx>

void AutLib::GeoLib::Entity_Box2d::Print(Standard_OStream & Ostream) const
{
	Ostream
		<< "P0 = ["
		<< xmin_
		<< ","
		<< ymin_
		<< "],  P1 = ["
		<< xmax_
		<< ","
		<< ymax_
		<< "]";
}

void AutLib::GeoLib::Entity_Box2d::ExportToPlt(fstream & File) const
{
	M_IO IO_TecPlot::ExportBox(*this, File);
}