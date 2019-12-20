#include <Mesh3d_SmoothingConfig.hxx>

static const Standard_Real DEFAULT_ACTIVESETFACTOR = 1.03;
static const Standard_Integer DEFAULT_MAXLINEITER = 50;
static const Standard_Real DEFAULT_MINSTEPSIZE = 1.0E-5;
static const Standard_Real DEFAULT_MINSMOOTHITERIMPROVE = 1.0E-5;
static const Standard_Integer DEFAULT_MaxITERATIONS = 5;

AutLib::MeshLib::Mesh3d_SmoothingConfig::Mesh3d_SmoothingConfig()
	: theActiveSetFactor_(DEFAULT_ACTIVESETFACTOR)
	, theMaxLineIterations_(DEFAULT_MAXLINEITER)
	, theMinStepSize_(DEFAULT_MINSTEPSIZE)
	, theMinSmoothingImprovement_(DEFAULT_MINSMOOTHITERIMPROVE)
	, theMaxIterations_(DEFAULT_MaxITERATIONS)
{
}

Standard_Integer AutLib::MeshLib::Mesh3d_SmoothingConfig::MaxLineIterations() const
{
	return theMaxLineIterations_;
}

Standard_Integer AutLib::MeshLib::Mesh3d_SmoothingConfig::MaxSmoothingIterations() const
{
	return theMaxIterations_;
}

Standard_Real AutLib::MeshLib::Mesh3d_SmoothingConfig::ActiveSetFactor() const
{
	return theActiveSetFactor_;
}

Standard_Real AutLib::MeshLib::Mesh3d_SmoothingConfig::MinStepSize() const
{
	return theMinStepSize_;
}

Standard_Real AutLib::MeshLib::Mesh3d_SmoothingConfig::MinSmoothingImprovement() const
{
	return theMinSmoothingImprovement_;
}