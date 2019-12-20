#include <Cad3d_ShellOnSolid.hxx>

#include <Entity_Box3d.hxx>
#include <Entity_Triangulation3d.hxx>
#include <Entity_Box3dTools.hxx>
#include <Entity_Triangulation3dTools.hxx>
#include <Merge_Triangulation3d.hxx>
#include <Cad3d_SurfaceOnSolid.hxx>
#include <TColEntity_HAry1dOfTriangulation3d.hxx>
#include <TColEntity_HBasicQueueOfTriangulation3d.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace GeoLib;

AutLib::CadLib::Cad3d_ShellOnSolid::Cad3d_ShellOnSolid()
{
}

AutLib::CadLib::Cad3d_ShellOnSolid::Cad3d_ShellOnSolid(Standard_Integer theIndex, const TColCad3d_HAry1dOfSurfaceOnSolid & theSurfaces)
	: theSurfaces_(theSurfaces)
	, theIndex_(theIndex)
{
}

void AutLib::CadLib::Cad3d_ShellOnSolid::Init(const Standard_Integer theIndex, const TColCad3d_HAry1dOfSurfaceOnSolid & theSurfaces)
{
	theSurfaces_ = theSurfaces;

	theIndex_ = theIndex;
}

void AutLib::CadLib::Cad3d_ShellOnSolid::SetIndex(const Standard_Integer theIndex)
{
	theIndex_ = theIndex;
}

Standard_Boolean AutLib::CadLib::Cad3d_ShellOnSolid::IsClosed() const
{
	forThose
	(
		Index,
		0, 
		MaxIndexOf(theSurfaces_)
	)
	{
		Debug_Null_Pointer(theSurfaces_[Index]);

		if (theSurfaces_[Index]->HasFreeEdge()) return Standard_False;
	}
	return Standard_True;
}

void AutLib::CadLib::Cad3d_ShellOnSolid::ExportToPlt(fstream & File) const
{
	TColEntity_HBasicQueueOfTriangulation3d QTriangulations;
	forThose
	(
		Index,
		0,
		MaxIndexOf(theSurfaces_)
	)
	{
		if (theSurfaces_[Index])
		{
			Global_Handle(Entity_Triangulation3d) Triangulation = new Entity_Triangulation3d;
			Entity_Triangulation3dTools::GetTriangulation(theSurfaces_[Index]->Triangulation(), *Triangulation);
			QTriangulations.EnQueue(Triangulation);
		}
	}

	TColEntity_HAry1dOfTriangulation3d Triangulations;
	QTriangulations.RetrieveTo(Triangulations);

	Merge_Triangulation3d Merge;
	Merge.Import(Triangulations);

	Merge.Merged()->ExportToPlt(File);

	FreeMemory(Triangulations);
}

void AutLib::CadLib::Cad3d_ShellOnSolid::CalcBoundingBox()
{
	if (theSurfaces_.IsEmpty()) { THROW_STANDARD_EXCEPTION("Empty List"); }

	Entity_Box3d Box(0, 0, 0, 0, 0, 0);
	forThose
	(
		Index,
		0,
		MaxIndexOf(theSurfaces_)
	)
	{
		Debug_Null_Pointer(theSurfaces_[Index]);

		Box = Entity_Box3dTools::Union(Box, theSurfaces_[Index]->BoundingBox());
	}
	theBox_ = Box;
}