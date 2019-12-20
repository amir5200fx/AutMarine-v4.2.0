#include <FvDiscreteDiv2d.hxx>

AutLib::FvLib::FvDiscreteDiv2d::FvDiscreteDiv2d
(
	FvMatrix & theAssembly,
	FvVectorField & theSources, 
	FvVectorField & theX,
	const FvMesh2d & theMesh
)
	: FvDiscrete2d(theAssembly, theSources, theX, theMesh)
{
}

AutLib::FvLib::FvDiscreteDiv2d::~FvDiscreteDiv2d()
{
}