#include <Mesh3d_TMeshAddElementInfo.hxx>

AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::Mesh3d_TMeshAddElementInfo()
	: theCreatedEdge3_(NULL)
	, theCreatedEdge4_(NULL)
	, theCreatedEdge5_(NULL)
	, theCreatedFacet0_(NULL)
	, theCreatedFacet1_(NULL)
	, theCreatedFacet2_(NULL)
	, thePairedEdge3_(NULL)
	, thePairedEdge4_(NULL)
	, thePairedEdge5_(NULL)
	, thePairedFacet0_(NULL)
	, thePairedFacet1_(NULL)
	, thePairedFacet2_(NULL)
{
}

void AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::Reset()
{
	thePairedEdge3_ = NULL;
	thePairedEdge4_ = NULL;
	thePairedEdge5_ = NULL;

	theCreatedEdge3_ = NULL;
	theCreatedEdge4_ = NULL;
	theCreatedEdge5_ = NULL;

	thePairedFacet0_ = NULL;
	thePairedFacet1_ = NULL;
	thePairedFacet2_ = NULL;

	theCreatedFacet0_ = NULL;
	theCreatedFacet1_ = NULL;
	theCreatedFacet2_ = NULL;
}