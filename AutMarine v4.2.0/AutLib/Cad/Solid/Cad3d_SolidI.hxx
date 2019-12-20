#pragma once
inline M_GEO Entity_Box3d AutLib::CadLib::Cad3d_Solid::BoundingBox(const Standard_Real Offset) const
{
	return theBoundingBox_.OffsetBox(Offset);
}

inline
Global_Handle(M_CAD Cad3d_EntitiesOnSolid) AutLib::CadLib::Cad3d_Solid::Vertices() const
{
	return theVertices_;
}

inline 
Global_Handle(M_CAD Cad3d_EntitiesOnSolid) AutLib::CadLib::Cad3d_Solid::PairedEdges() const
{
	return thePairedEdges_;
}

inline 
Global_Handle(M_CAD Cad3d_EntitiesOnSolid) AutLib::CadLib::Cad3d_Solid::Surfaces() const
{
	return theSurfaces_;
}

inline 
Standard_Integer AutLib::CadLib::Cad3d_Solid::NbVertices() const
{
	Debug_Null_Pointer(theVertices_);
	return theVertices_->Size();
}

inline 
Standard_Integer AutLib::CadLib::Cad3d_Solid::NbPairedEdges() const
{
	Debug_Null_Pointer(thePairedEdges_);
	return thePairedEdges_->Size();
}

inline 
Standard_Integer AutLib::CadLib::Cad3d_Solid::NbSurfaces() const
{
	Debug_Null_Pointer(theSurfaces_);
	return theSurfaces_->Size();
}

inline 
Standard_Integer AutLib::CadLib::Cad3d_Solid::NbHoles() const
{
	return theInnerShells_.Size();
}

inline
Standard_String AutLib::CadLib::Cad3d_Solid::Name() const
{
	return theName_;
}

inline
void AutLib::CadLib::Cad3d_Solid::RetrieveVerticesTo(TColCad3d_HAry1dOfEntityOnSolid & theVertices) const
{
	Debug_Null_Pointer(theVertices_);
	theVertices_->RetrieveTo(theVertices);
}

inline 
void AutLib::CadLib::Cad3d_Solid::RetrievePairedEdgesTo(TColCad3d_HAry1dOfEntityOnSolid & theEdges) const
{
	Debug_Null_Pointer(thePairedEdges_);
	thePairedEdges_->RetrieveTo(theEdges);
}

inline 
void AutLib::CadLib::Cad3d_Solid::RetrieveSurfacesTo(TColCad3d_HAry1dOfEntityOnSolid & theSurfaces) const
{
	Debug_Null_Pointer(theSurfaces_);
	theSurfaces_->RetrieveTo(theSurfaces);
}