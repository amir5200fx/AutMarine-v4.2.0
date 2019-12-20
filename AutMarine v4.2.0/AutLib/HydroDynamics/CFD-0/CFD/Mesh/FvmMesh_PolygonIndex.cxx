#include <FvmMesh_PolygonIndex.hxx>

AutLib::FvmLib::FvmMesh_PolygonIndex::FvmMesh_PolygonIndex()
{
}

AutLib::FvmLib::FvmMesh_PolygonIndex::FvmMesh_PolygonIndex(const TColStd_Ary1dOfInteger & theValue)
	: theValue_(theValue)
{
}

void AutLib::FvmLib::FvmMesh_PolygonIndex::Init(const TColStd_Ary1dOfInteger & theValue)
{
	theValue_ = theValue;
}

void AutLib::FvmLib::FvmMesh_PolygonIndex::SetValue
(
	const Standard_Integer theIndex,
	const Standard_Integer theValue
)
{
	Debug_Bad_Index_Array1(theIndex, theValue_);
	theValue_.SetValue(theIndex, theValue);
}

Standard_IStream & AutLib::FvmLib::operator>>(Standard_IStream & Istream, FvmMesh_PolygonIndex & theObject)
{
	Standard_Integer Size;
	Istream >> Size;

	TColStd_Ary1dOfInteger X(Size);
	forThose(Index, 0, MaxIndexOf(X))
		Istream >> X[Index];
	theObject.Init(X);
	return Istream;
}