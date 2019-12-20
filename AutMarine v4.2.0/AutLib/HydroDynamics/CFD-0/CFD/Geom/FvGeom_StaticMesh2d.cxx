#include <FvGeom_StaticMesh2d.hxx>

#include <FvGeom_Node2d.hxx>
#include <FvGeom_Face2d.hxx>
#include <FvGeom_Element2d.hxx>

AutLib::FvLib::FvGeom_StaticMesh2d::FvGeom_StaticMesh2d()
{
}

void AutLib::FvLib::FvGeom_StaticMesh2d::Import(fstream & File)
{
	Standard_String A;
	Standard_Integer nbNodes;
	File >> A >> nbNodes;

	theNodes_.Resize(nbNodes);
	forThose(Index, 0, MaxIndexOf(theNodes_))
		theNodes_[Index].Import(File);

	Standard_Integer nbElements;
	File >> A >> nbElements;
	theElements_.Resize(nbElements);

	forThose(Index, 0, MaxIndexOf(theElements_))
		theElements_[Index].Import(File);

	Standard_Integer nbFaces;
	File >> A >> nbFaces;
	theFaces_.Resize(nbFaces);

	forThose(Index, 0, MaxIndexOf(theFaces_))
		theFaces_[Index].Import(File);
}