#pragma once
inline
Standard_Boolean AutLib::GeoLib::Entity_Element3dTools::IsLess(Global_Handle(Entity_Element3d) const & Element0, Global_Handle(Entity_Element3d) const & Element1)
{
	Debug_Null_Pointer(Element0);
	Debug_Null_Pointer(Element1);

	return Element0->Index() < Element1->Index();
}

inline
void AutLib::GeoLib::Entity_Element3dTools::EdgeIndices
(
	const Standard_Integer Index,
	Standard_Integer & V1, 
	Standard_Integer & V2
)
{
	static Standard_Integer Indices[12] =
	{
		2, 3, 3, 1, 1, 2, 1, 4, 2, 4, 3, 4
	};

	Debug_Bad_Index(Index, 0, 11);

	V1 = Indices[2 * Index];
	V2 = Indices[2 * Index + 1];
}

inline 
void AutLib::GeoLib::Entity_Element3dTools::FacetIndices
(
	const Standard_Integer Index,
	Standard_Integer & V1,
	Standard_Integer & V2, 
	Standard_Integer & V3
)
{
	static Standard_Integer Indices[12] =
	{
		2, 3, 4, 3, 1, 4, 4, 1, 2, 2, 1, 3
	};

	Debug_Bad_Index(Index, 0, 11);

	V1 = Indices[3 * Index];
	V2 = Indices[3 * Index + 1];
	V3 = Indices[3 * Index + 2];
}