#include <FvNavierStokes.hxx>

AutLib::FvLib::FvNavierStokes::FvNavierStokes
(
	const FvMesh2d & theMesh, 
	const FvParameters & theParameters,
	const FvBC & theBoundaryCondition,
	const FvVariables2d & theVariables,
	const FvMaterial& theMaterial
)
	: theMesh_(theMesh)
	, theParameters_(theParameters)
	, theBoundaryCondition_(theBoundaryCondition)
	, theVariables_(theVariables)
	, theMaterial_(theMaterial)
{
}