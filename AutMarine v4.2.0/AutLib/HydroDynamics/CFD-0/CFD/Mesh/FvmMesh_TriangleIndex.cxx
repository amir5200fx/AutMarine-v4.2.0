#include <FvmMesh_TriangleIndex.hxx>

AutLib::FvmLib::FvmMesh_TriangleIndex::FvmMesh_TriangleIndex()
{
}

AutLib::FvmLib::FvmMesh_TriangleIndex::FvmMesh_TriangleIndex
(
	const Standard_Integer theV0, 
	const Standard_Integer theV1, 
	const Standard_Integer theV2
)
{
	theValue_[0] = theV0;
	theValue_[1] = theV1;
	theValue_[2] = theV2;
}

void AutLib::FvmLib::FvmMesh_TriangleIndex::Init
(
	const Standard_Integer theV0, 
	const Standard_Integer theV1, 
	const Standard_Integer theV2
)
{
	theValue_[0] = theV0;
	theValue_[1] = theV1;
	theValue_[2] = theV2;
}

void AutLib::FvmLib::FvmMesh_TriangleIndex::SetV0(const Standard_Integer theIndex)
{
	theValue_[0] = theIndex;
}

void AutLib::FvmLib::FvmMesh_TriangleIndex::SetV1(const Standard_Integer theIndex)
{
	theValue_[1] = theIndex;
}

void AutLib::FvmLib::FvmMesh_TriangleIndex::SetV2(const Standard_Integer theIndex)
{
	theValue_[2] = theIndex;
}

Standard_IStream & AutLib::FvmLib::operator>>(Standard_IStream & Istream, FvmMesh_TriangleIndex & theObject)
{
	Standard_Integer V0, V1, V2;
	Istream >> V0 >> V1 >> V2;

	theObject.Init(V0, V1, V2);
	return Istream;
}