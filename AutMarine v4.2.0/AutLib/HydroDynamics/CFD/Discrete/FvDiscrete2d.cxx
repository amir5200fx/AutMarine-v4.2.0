#include <FvDiscrete2d.hxx>

AutLib::FvLib::FvDiscrete2d::FvDiscrete2d
(
	FvMatrix & theAssembly,
	FvVectorField & theSources, 
	FvVectorField & theX, 
	const FvMesh2d & theMesh
)
	: theAssembly_(theAssembly)
	, theSources_(theSources_)
	, theX_(theX)
	, theMesh_(theMesh)
{
}

AutLib::FvLib::FvDiscrete2d::~FvDiscrete2d()
{
}