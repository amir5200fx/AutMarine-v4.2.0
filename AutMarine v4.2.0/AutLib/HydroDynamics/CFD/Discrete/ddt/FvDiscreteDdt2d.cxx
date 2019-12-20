#include <FvDiscreteDdt2d.hxx>

AutLib::FvLib::FvDiscreteDdt2d::FvDiscreteDdt2d
(
	FvMatrix & theAssembly,
	FvVectorField & theSources, 
	FvVectorField & theX,
	const FvMesh2d & theMesh
)
	: FvDiscrete2d(theAssembly, theSources, theX, theMesh)
{
}

AutLib::FvLib::FvDiscreteDdt2d::~FvDiscreteDdt2d()
{
}