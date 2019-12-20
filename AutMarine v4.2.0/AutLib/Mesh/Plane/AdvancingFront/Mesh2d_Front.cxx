#include <Mesh2d_Front.hxx>

#include <Mesh2d_EdgeTools.hxx>

AutLib::MeshLib::Mesh2d_Front::Mesh2d_Front()
	: theLevelNb_(0)
	, theLevelMaxIndex_(0)
{
	theSortedEdges_.SetFunction(&Mesh2d_EdgeTools::LengthOf);
}