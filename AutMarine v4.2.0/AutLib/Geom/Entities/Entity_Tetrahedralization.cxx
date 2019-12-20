#include <Entity_Tetrahedralization.hxx>

#include <IO_Tecplot.hxx>

AutLib::GeoLib::Entity_Tetrahedralization::Entity_Tetrahedralization()
{
}

AutLib::GeoLib::Entity_Tetrahedralization::Entity_Tetrahedralization
(
	const TColGeom_Ary1dOfPnt3d & Coords, 
	const TColEntity_Ary1dOfTetrahedronIndex & Tetrahedrons
)
	: thePoints_(Coords)
	, theTetrahedros_(Tetrahedrons)
{
}

void AutLib::GeoLib::Entity_Tetrahedralization::ExportToPlt(fstream & File) const
{
	M_IO IO_TecPlot::ExportMesh(thePoints_, theTetrahedros_, File);
}