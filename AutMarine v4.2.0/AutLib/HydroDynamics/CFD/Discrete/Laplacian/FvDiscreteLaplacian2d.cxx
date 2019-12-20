#include <FvDiscreteLaplacian2d.hxx>

AutLib::FvLib::FvDiscreteLaplacian2d::FvDiscreteLaplacian2d
(
	FvMatrix & theAssembly, 
	FvVectorField & theSources,
	FvVectorField & theX, 
	const FvMesh2d & theMesh
)
	: FvDiscrete2d(theAssembly, theSources, theX, theMesh)
{
}

AutLib::FvLib::FvDiscreteLaplacian2d::~FvDiscreteLaplacian2d()
{
}