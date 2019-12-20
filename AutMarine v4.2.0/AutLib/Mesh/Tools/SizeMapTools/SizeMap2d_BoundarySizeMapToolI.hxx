#pragma once
inline 
Standard_Integer AutLib::MeshLib::SizeMap2d_BoundarySizeMapTool::NbPointPatches() const
{
	return thePointPatches_.Size();
}

inline 
Standard_Integer AutLib::MeshLib::SizeMap2d_BoundarySizeMapTool::NbCurvePatches() const
{
	return theCurvePatches_.Size();
}

inline 
Standard_Boolean AutLib::MeshLib::SizeMap2d_BoundarySizeMapTool::RemovePointPatch(const Standard_String PatchName)
{
	if (thePointPatches_.IsEmpty()) { return Standard_False; }

	Standard_Integer N0 = NbPointPatches();
	thePointPatches_.Remove(PatchName);

	if (NbPointPatches() == N0) return Standard_False;
	return Standard_True;
}

inline 
Standard_Boolean AutLib::MeshLib::SizeMap2d_BoundarySizeMapTool::RemoveCurvePatch(const Standard_String PatchName)
{
	if (theCurvePatches_.IsEmpty()) { return Standard_False; }

	Standard_Integer N0 = NbCurvePatches();
	theCurvePatches_.Remove(PatchName);

	if (NbCurvePatches() == N0) return Standard_False;
	return Standard_True;
}

inline 
void AutLib::MeshLib::SizeMap2d_BoundarySizeMapTool::ImportPointPatch(const Standard_String PatchName)
{
	thePointPatches_.EnQueue(PatchName);
}

inline 
void AutLib::MeshLib::SizeMap2d_BoundarySizeMapTool::ImportCurvePatch(const Standard_String PatchName)
{
	theCurvePatches_.EnQueue(PatchName);
}

inline 
void AutLib::MeshLib::SizeMap2d_BoundarySizeMapTool::RetrievePointPatchesTo(TColStd_Ary1dOfString & Patches) const
{
	thePointPatches_.RetrieveTo(Patches);
}

inline 
void AutLib::MeshLib::SizeMap2d_BoundarySizeMapTool::RetrieveCurvePatchesTo(TColStd_Ary1dOfString & Patches) const
{
	theCurvePatches_.RetrieveTo(Patches);
}