#include <Entity_Triangulation2d.hxx>

#include <Primitive_Field.hxx>
#include <IO_Tecplot.hxx>

AutLib::GeoLib::Entity_Triangulation2d::Entity_Triangulation2d()
{
}

AutLib::GeoLib::Entity_Triangulation2d::Entity_Triangulation2d
(
	const TColGeom_Ary1dOfPnt2d & Coords,
	const TColEntity_Ary1dOfTriangleIndex & Triangles
)
	: thePoints_(Coords)
	, theTriangles_(Triangles)
{
}

void AutLib::GeoLib::Entity_Triangulation2d::ExportToPlt(fstream & File) const
{
	M_IO IO_TecPlot::ExportMesh(thePoints_, theTriangles_, File);
}

void AutLib::GeoLib::Entity_Triangulation2d::ExportToPlt
(
	const Primitive_Field & Field, 
	fstream & File
) const
{
	if (Field.NbPoints() NOT_EQUAL NbPoints()) { THROW_STANDARD_EXCEPTION(" The Field is not compatible with the Mesh"); }
	if (Field.VariablesName().empty()) { THROW_STANDARD_EXCEPTION(" Variables have no Name"); }

	M_IO IO_TecPlot::ExportField(*this, Field, File);
}