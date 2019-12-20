#include <Mesh2d_TMeshAddElementInfo.hxx>

AutLib::MeshLib::Mesh2d_TMeshAddElementInfo::Mesh2d_TMeshAddElementInfo()
	: theCreatedEdge0_(NULL)
	, theCreatedEdge1_(NULL)
	, theCreatedElement_(NULL)
	, theCurrent_(NULL)
	, thePairedEdge0_(NULL)
	, thePairedEdge1_(NULL)
	, theValid_(NULL)
{
}

void AutLib::MeshLib::Mesh2d_TMeshAddElementInfo::Reset()
{
	theCreatedEdge0_ = NULL;
	theCreatedEdge1_ = NULL;
	theCreatedElement_ = NULL;
	theCurrent_ = NULL;
	thePairedEdge0_ = NULL;
	thePairedEdge1_ = NULL;
	theValid_ = NULL;
}