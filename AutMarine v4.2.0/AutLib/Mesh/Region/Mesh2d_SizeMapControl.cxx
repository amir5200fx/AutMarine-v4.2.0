#include <Mesh2d_SizeMapControl.hxx>

#include <Global_Debug.hxx>
#include <SizeMap2d_UnionSizeMaps.hxx>
#include <SizeMap2d_SizeMapTool.hxx>

using namespace AutLib;
using namespace MeshLib;
using namespace GeoLib;

AutLib::MeshLib::Mesh2d_SizeMapControl::~Mesh2d_SizeMapControl()
{
	ReleaseMemory();
}

void AutLib::MeshLib::Mesh2d_SizeMapControl::CreateNewMap(const Standard_String & theName)
{
	CloseProgram("It's a virtual function");
}

void AutLib::MeshLib::Mesh2d_SizeMapControl::Print(Standard_OStream & Ostream) const
{
	Ostream << " Nb. of Boundaries = " << Size() << endl;
	Ostream << " Boundary List: " << endl;

	TColSizeMap2d_StringMapOfHSizeMapTool::const_iterator Iter = theBoundaries_.begin();
	while (Iter NOT_EQUAL theBoundaries_.end())
	{
		Ostream << Iter->first << endl;
		Iter++;
	}
}

void AutLib::MeshLib::Mesh2d_SizeMapControl::Remove(const Standard_String & theName)
{
	TColSizeMap2d_StringMapOfHSizeMapTool::iterator Iter = theBoundaries_.find(theName);
	if (Iter EQUAL theBoundaries_.end())
	{
		THROW_STANDARD_EXCEPTION(" Not found the Item");
		return;
	}
	theBoundaries_.erase(Iter);
}

void AutLib::MeshLib::Mesh2d_SizeMapControl::RetrieveSizeMapsTo(TColSizeMap2d_HAry1dOfSizeMapTool & theSizeMaps) const
{
	theSizeMaps.Resize(Size());

	Standard_Integer K = 0;
	TColSizeMap2d_StringMapOfHSizeMapTool::const_iterator Iter = theBoundaries_.begin();
	while (Iter NOT_EQUAL theBoundaries_.end())
	{
		theSizeMaps.SetValue(K++, Iter->second);
		Iter++;
	}
}

void AutLib::MeshLib::Mesh2d_SizeMapControl::ReleaseMemory()
{
	TColSizeMap2d_StringMapOfHSizeMapTool::iterator Iter = theBoundaries_.begin();
	while (Iter NOT_EQUAL theBoundaries_.end())
	{
		FreePointer(Iter->second);
		Iter++;
	}
}

Global_Handle(GeoMesh_BackGroundMesh2d) AutLib::MeshLib::Mesh2d_SizeMapControl::CalcSizeMap() const
{
	TColSizeMap2d_HAry1dOfSizeMapTool Maps;
	RetrieveSizeMapsTo(Maps);

	if (Maps.IsEmpty()) { return 0; }

	if (Maps.Size() EQUAL 1) 
	{ 
		Debug_Null_Pointer(Maps[0]);

		return Maps[0]->BackGroundMesh();
	}

	SizeMap2d_UnionSizeMaps Operator;
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

	Debug_If_Condition_Message(NOT Operator.IsDone(), "The Operator is not performed");

	return Operator.BackGroundMesh();
}

AutLib::MeshLib::Mesh2d_SizeMapControl::Mesh2d_SizeMapControl
(
	const Global_Handle(Mesh_ReferenceValues) theReference,
	const Global_Handle(M_CAD Cad2d_Plane) thePlane
)
	: theReference_(theReference)
	, thePlane_(thePlane)
{
}

void AutLib::MeshLib::Mesh2d_SizeMapControl::ImportMap
(
	const Global_Handle(SizeMap2d_SizeMapTool) theMap,
	const Standard_String theName
)
{
	std::pair<TColSizeMap2d_StringMapOfHSizeMapTool::iterator, Standard_Boolean> Insert;
	Insert = theBoundaries_.insert(std::pair<Standard_String, Global_Handle(SizeMap2d_SizeMapTool)>(theName, (Global_Handle(SizeMap2d_SizeMapTool))theMap));

	if (Insert.second EQUAL Standard_False)
	{
		ImportMap(theMap, theName + "(1)");
		return;
	}
}