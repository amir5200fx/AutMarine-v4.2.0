#include <Mesh3d_SizeMapControl.hxx>

#include <Global_Debug.hxx>
#include <SizeMap3d_UnionSizeMaps.hxx>
#include <SizeMap3d_SizeMapTool.hxx>

using namespace AutLib;
using namespace MeshLib;
using namespace GeoLib;

AutLib::MeshLib::Mesh3d_SizeMapControl::~Mesh3d_SizeMapControl()
{
	ReleaseMemory();
}

void AutLib::MeshLib::Mesh3d_SizeMapControl::CreateNewMap(const Standard_String & theName)
{
	CloseProgram("It's a virtual function");
}

void AutLib::MeshLib::Mesh3d_SizeMapControl::Print(Standard_OStream & Ostream) const
{
	Ostream << " Nb. of Boundaries = " << Size() << endl;
	Ostream << " Boundary List: " << endl;

	TColSizeMap3d_StringMapOfHSizeMapTool::const_iterator Iter = theBoundaries_.begin();
	while (Iter NOT_EQUAL theBoundaries_.end())
	{
		Ostream << Iter->first << endl;
		Iter++;
	}
}

void AutLib::MeshLib::Mesh3d_SizeMapControl::Remove(const Standard_String & theName)
{
	TColSizeMap3d_StringMapOfHSizeMapTool::iterator Iter = theBoundaries_.find(theName);
	if (Iter EQUAL theBoundaries_.end())
	{
		THROW_STANDARD_EXCEPTION(" Not found the Item");
		return;
	}
	theBoundaries_.erase(Iter);
}

void AutLib::MeshLib::Mesh3d_SizeMapControl::RetrieveSizeMapsTo(TColSizeMap3d_HAry1dOfSizeMapTool & theSizeMaps) const
{
	theSizeMaps.Resize(Size());

	Standard_Integer K = 0;
	TColSizeMap3d_StringMapOfHSizeMapTool::const_iterator Iter = theBoundaries_.begin();
	while (Iter NOT_EQUAL theBoundaries_.end())
	{
		theSizeMaps.SetValue(K++, Iter->second);
		Iter++;
	}
}

void AutLib::MeshLib::Mesh3d_SizeMapControl::ReleaseMemory()
{
	TColSizeMap3d_StringMapOfHSizeMapTool::iterator Iter = theBoundaries_.begin();
	while (Iter NOT_EQUAL theBoundaries_.end())
	{
		FreePointer(Iter->second);
		Iter++;
	}
}

Global_Handle(M_GEO GeoMesh_BackGroundMesh3d) AutLib::MeshLib::Mesh3d_SizeMapControl::CalcSizeMap() const
{
	TColSizeMap3d_HAry1dOfSizeMapTool Maps;
	RetrieveSizeMapsTo(Maps);
	/*Open_OutputFile_TecPlot(Plot, "test");
	forThose(Index, 0, MaxIndexOf(Maps))
		Maps[Index]->ExportContourToPlt(Plot);*/

	if (Maps.IsEmpty()) { return 0; }

	if (Maps.Size() EQUAL 1)
	{
		Debug_Null_Pointer(Maps[0]);

		return Maps[0]->BackGroundMesh();
	}

	SizeMap3d_UnionSizeMaps Operator;
	forThose
	(
		Index,
		0,
		MaxIndexOf(Maps)
	)
	{
		Debug_Null_Pointer(Maps[Index]);

		Operator.ImportSizeMap(Maps[Index]->BackGroundMesh());
	}
	Operator.Perform();
	/*Operator.ExportBackMeshToPlt(Plot);
	exit(1);*/
	Debug_If_Condition_Message(NOT Operator.IsDone(), "The Operator is not performed");

	return Operator.BackGroundMesh();
}

AutLib::MeshLib::Mesh3d_SizeMapControl::Mesh3d_SizeMapControl
(
	const Global_Handle(Mesh_ReferenceValues) theReference, 
	const Global_Handle(M_CAD Cad3d_Solid)theSolid
)
	: theReference_(theReference)
	, theSolid_(theSolid)
{
}

void AutLib::MeshLib::Mesh3d_SizeMapControl::ImportMap
(
	const Global_Handle(SizeMap3d_SizeMapTool) theMap, 
	const Standard_String theName
)
{
	std::pair<TColSizeMap3d_StringMapOfHSizeMapTool::iterator, Standard_Boolean> Insert;
	Insert = theBoundaries_.insert(std::pair<Standard_String, Global_Handle(SizeMap3d_SizeMapTool)>(theName, (Global_Handle(SizeMap3d_SizeMapTool))theMap));

	if (Insert.second EQUAL Standard_False)
	{
		ImportMap(theMap, theName + "(1)");
		return;
	}
}