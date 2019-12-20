#include <FvmMesh_ElementIndex.hxx>

#include <Standard_String.hxx>
#include <FvmMesh_TriangleIndex.hxx>
#include <FvmMesh_QuadrangleIndex.hxx>
#include <FvmMesh_PolygonIndex.hxx>

AutLib::FvmLib::FvmMesh_ElementIndex::FvmMesh_ElementIndex()
{
}

Standard_IStream & AutLib::FvmLib::operator>>(Standard_IStream & Istream, Global_Handle(FvmMesh_ElementIndex)& theObject)
{
	Standard_String String;

	Istream >> String;

}