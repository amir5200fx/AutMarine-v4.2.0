#include <FvPressure2d.hxx>

AutLib::FvLib::FvPressure2d::FvPressure2d
(
	const FvMesh2d & theMesh, 
	const FvParameters & theParameters, 
	const FvBC & theBoundaryCondition, 
	const FvVariables2d & theVariables
)
	: FvNavierStokes(theMesh, theParameters, theBoundaryCondition, theVariables)
{
}

void AutLib::FvLib::FvPressure2d::CalcPressure()
{

}