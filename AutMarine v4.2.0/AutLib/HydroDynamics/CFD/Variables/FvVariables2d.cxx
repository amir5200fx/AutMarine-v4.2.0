#include <FvVariables2d.hxx>

AutLib::FvLib::FvVariables2d::FvVariables2d(FvMemory2d & theMemory)
	: theCellVariables0_(theMemory.xU0(), theMemory.xV0(), theMemory.xP0())
	, theCellVariables_(theMemory.xU(), theMemory.xV(), theMemory.xP())
	, theFaceVariables_(theMemory.xUf(), theMemory.xVf(), theMemory.xPf())
	, theSources_(theMemory.Bu(), theMemory.Bv())
	, theCorrectionSources_(theMemory.Hu(), theMemory.Hv())
	, theFluxVelocity_(theMemory.Uf())
	, theAssembly_(theMemory.Ac(), theMemory.Am())
{
}