#include <Mesh3d_CycleInfo.hxx>

static const Standard_Real DEFAULT_MIN_DISTANCE_FACTOR = 0.2;
static const Standard_Real DEFAULT_MIN_EDGE_DISTANCE_FACTOR = 0.05;

AutLib::MeshLib::Mesh3d_CycleInfo::Mesh3d_CycleInfo()
	: theCreated_(NULL)
	, theValid_(NULL)
	, IsAppendNewPoint_(Standard_False)
	, theNewPointCondition_(Mesh3d_NewPoint)
	, theType_(Mesh3d_Aft_Generation)
	, theElementSize_(0)
	, theSearchingRadius_(0)
	, theSearchingRadius1_(0)
	, theSearchingRadius2_(0)
	, theMinDistance_(DEFAULT_MIN_DISTANCE_FACTOR)
	, theMinEdgeDistance_(DEFAULT_MIN_EDGE_DISTANCE_FACTOR)
	, theCoord_(Geom_Pnt3d())
	, theCurrent_(NULL)
	, thePairedFacet0_(NULL)
	, thePairedFacet1_(NULL)
	, thePairedFacet2_(NULL)
	, thePairedEdge3_(NULL)
	, thePairedEdge4_(NULL)
	, thePairedEdge5_(NULL)
	, theCreatedElement_(NULL)
{
}

void AutLib::MeshLib::Mesh3d_CycleInfo::Reset()
{
	static const Geom_Pnt3d ZeroPoint = Geom_Pnt3d();

	theCreated_ = NULL;
	theValid_ = NULL;

	IsAppendNewPoint_ = Standard_False;

	theNewPointCondition_ = Mesh3d_NewPoint;
	//theType_ = Mesh3d_Aft_Generation;

	theElementSize_ = 0;

	theSearchingRadius_ = 0;
	theSearchingRadius1_ = 0;
	theSearchingRadius2_ = 0;

	theMinDistance_ = DEFAULT_MIN_DISTANCE_FACTOR;

	theCoord_ = ZeroPoint;

	theCurrent_ = NULL;

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

	theCreatedElement_ = NULL;
}