#include <Mesh2d_CycleInfo.hxx>

static const Standard_Real DEFAULT_MIN_DISTANCE_FACTOR = 0.2;

AutLib::MeshLib::Mesh2d_CycleInfo::Mesh2d_CycleInfo()
	: theCreated_(NULL)
	, theValid_(NULL)
	, IsAppendNewPoint_(Standard_False)
	, theNewPointCondition_(Mesh2d_NewPoint)
	, theType_(Mesh2d_Aft_Generation)
	, theElementSize_(0)
	, theSearchingRadius_(0)
	, theSearchingRadius1_(0)
	, theSearchingRadius2_(0)
	, theMinDistance_(DEFAULT_MIN_DISTANCE_FACTOR)
	, theCoord_(Geom_Pnt2d())
	, theCurrent_(NULL)
	, thePairedEdge0_(NULL)
	, thePairedEdge1_(NULL)
	, theCreatedEdge0_(NULL)
	, theCreatedEdge1_(NULL)
	, theCreatedElement_(NULL)
{
}

void AutLib::MeshLib::Mesh2d_CycleInfo::Reset()
{
	static const Geom_Pnt2d ZeroPoint = Geom_Pnt2d();

	theCreated_ = NULL;
	theValid_ = NULL;

	IsAppendNewPoint_ = Standard_False;

	theNewPointCondition_ = Mesh2d_NewPoint;
	//theType_ = Mesh3d_Aft_Generation;

	theElementSize_ = 0;

	theSearchingRadius_ = 0;
	theSearchingRadius1_ = 0;
	theSearchingRadius2_ = 0;

	theMinDistance_ = DEFAULT_MIN_DISTANCE_FACTOR;

	theCoord_ = ZeroPoint;

	theCurrent_ = NULL;

	thePairedEdge0_ = NULL;
	thePairedEdge1_ = NULL;

	theCreatedEdge0_ = NULL;
	theCreatedEdge1_ = NULL;

	theCreatedElement_ = NULL;
}