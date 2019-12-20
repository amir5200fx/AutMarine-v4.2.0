#pragma once
inline
Standard_Real AutLib::MeshLib::SizeMap3d_PrimitiveShapeSource::ElementSize(const Geom_Pnt3d & theCoord) const
{
	Standard_Boolean Sense;
	Standard_Real Size = theSource_.ElementSize(theCoord, Sense);

	if (Sense) return Size;
	else return 1.0;
}

inline 
Standard_Real AutLib::MeshLib::SizeMap3d_PrimitiveShapeSource::ElementSize
(
	const Geom_Pnt3d & theCoord,
	Standard_Boolean & theSense
) const
{
	Standard_Real Size = theSource_.ElementSize(theCoord, theSense);

	if (theSense) return Size;
	else return 1.0;
}

inline
const M_GEO Entity_Box3d & AutLib::MeshLib::SizeMap3d_PrimitiveShapeSource::BoundingBox() const
{
	return theBoundingBox_;
}

inline 
const M_GEO GeoMesh_BackGroundMesh3d & AutLib::MeshLib::SizeMap3d_PrimitiveShapeSource::Mesh() const
{
	return theSource_;
}