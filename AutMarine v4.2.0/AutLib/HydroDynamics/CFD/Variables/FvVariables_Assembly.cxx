#include <FvVariables_Assembly.hxx>

AutLib::FvLib::FvVariables_Assembly::FvVariables_Assembly
(
	FvMatrix & theContinuity, 
	FvMatrix & theMomentum
)
	: theAc_(theContinuity)
	, theAm_(theMomentum)
{
}