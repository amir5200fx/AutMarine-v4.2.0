#include <Mesh_LaplacianSmoothingInfo.hxx>

static const Standard_Integer DEFAULT_MAX_LEVELS = 3;
static const Standard_Real DEFAULT_UNDER_RELAXATION = 0.8;

AutLib::MeshLib::Mesh_LaplacianSmoothingInfo::Mesh_LaplacianSmoothingInfo()
	: theMaxLevels_(DEFAULT_MAX_LEVELS)
	, theUnderRelaxation_(DEFAULT_UNDER_RELAXATION)
	, BeApply_(Standard_False)
{
}

Standard_Integer AutLib::MeshLib::Mesh_LaplacianSmoothingInfo::MaxLevels() const
{
	return theMaxLevels_;
}

Standard_Real AutLib::MeshLib::Mesh_LaplacianSmoothingInfo::UnderRelaxation() const
{
	return theUnderRelaxation_;
}

Standard_Boolean AutLib::MeshLib::Mesh_LaplacianSmoothingInfo::beApply() const
{
	return BeApply_;
}

void AutLib::MeshLib::Mesh_LaplacianSmoothingInfo::SetMaxLevels(const Standard_Integer MaxLevels)
{
	theMaxLevels_ = MaxLevels;
}

void AutLib::MeshLib::Mesh_LaplacianSmoothingInfo::SetUnderRelaxation(const Standard_Real UnderRelaxation)
{
	theUnderRelaxation_ = UnderRelaxation;
}

void AutLib::MeshLib::Mesh_LaplacianSmoothingInfo::SetApply(const Standard_Boolean Apply)
{
	BeApply_ = Apply;
}