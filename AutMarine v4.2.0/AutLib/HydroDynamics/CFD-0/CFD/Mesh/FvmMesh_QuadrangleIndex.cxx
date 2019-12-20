#include <FvmMesh_QuadrangleIndex.hxx>

AutLib::FvmLib::FvmMesh_QuadrangleIndex::FvmMesh_QuadrangleIndex()
{
}

AutLib::FvmLib::FvmMesh_QuadrangleIndex::FvmMesh_QuadrangleIndex
(
	const Standard_Integer theV0,
	const Standard_Integer theV1, 
	const Standard_Integer theV2,
	const Standard_Integer theV3
)
{
	theValue_[0] = theV0;
	theValue_[1] = theV1;
	theValue_[2] = theV2;
	theValue_[3] = theV3;
}

void AutLib::FvmLib::FvmMesh_QuadrangleIndex::Init
(
	const Standard_Integer theV0,
	const Standard_Integer theV1,
	const Standard_Integer theV2,
	const Standard_Integer theV3
)
{
	theValue_[0] = theV0;
	theValue_[1] = theV1;
	theValue_[2] = theV2;
	theValue_[3] = theV3;
}

void AutLib::FvmLib::FvmMesh_QuadrangleIndex::SetV0(const Standard_Integer theIndex)
{
	theValue_[0] = theIndex;
}

void AutLib::FvmLib::FvmMesh_QuadrangleIndex::SetV1(const Standard_Integer theIndex)
{
	theValue_[1] = theIndex;
}

void AutLib::FvmLib::FvmMesh_QuadrangleIndex::SetV2(const Standard_Integer theIndex)
{
	theValue_[2] = theIndex;
}

void AutLib::FvmLib::FvmMesh_QuadrangleIndex::SetV3(const Standard_Integer theIndex)
{
	theValue_[3] = theIndex;
}

void AutLib::FvmLib::FvmMesh_QuadrangleIndex::SetValue(const Standard_Integer theIndex, const Standard_Integer theValue)
{
	Debug_If_Condition_Message(NOT INSIDE(theIndex, 0, 3), "Invalid Index");
	theValue_[theIndex] = theValue;
}

Standard_IStream & AutLib::FvmLib::operator>>(Standard_IStream & Istream, FvmMesh_QuadrangleIndex & theObject)
{
	Standard_Integer V0, V1, V2, V3;
	Istream >> V0, V1 >> V2 >> V3;
	theObject.Init(V0, V1, V2, V3);
	return Istream;
}