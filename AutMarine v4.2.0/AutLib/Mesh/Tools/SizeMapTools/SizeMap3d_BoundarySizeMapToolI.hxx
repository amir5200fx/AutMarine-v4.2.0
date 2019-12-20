#pragma once
inline
Standard_Integer AutLib::MeshLib::SizeMap3d_BoundarySizeMapTool::NbEntityPatches() const
{
	return theEntityPatches_.Size();
}

inline 
Standard_Boolean AutLib::MeshLib::SizeMap3d_BoundarySizeMapTool::RemoveEntityPatch(const Standard_String PatchName)
{
	if (theEntityPatches_.IsEmpty()) { return Standard_False; }

	Standard_Integer N0 = NbEntityPatches();
	theEntityPatches_.Remove(PatchName);

	if (NbEntityPatches() == N0) return Standard_False;
	return Standard_True;
}

inline 
void AutLib::MeshLib::SizeMap3d_BoundarySizeMapTool::ImportEntityPatch(const Standard_String PatchName)
{
	theEntityPatches_.EnQueue(PatchName);
}

inline 
void AutLib::MeshLib::SizeMap3d_BoundarySizeMapTool::RetrieveEntityPatchesTo(TColStd_Ary1dOfString & Patches) const
{
	theEntityPatches_.RetrieveTo(Patches);
}