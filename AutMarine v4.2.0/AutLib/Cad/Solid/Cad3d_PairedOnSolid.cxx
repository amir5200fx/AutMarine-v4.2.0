#include <Cad3d_PairedOnSolid.hxx>

#include <Entity_PolyLine3d.hxx>
#include <Cad3d_EdgeOnSolid.hxx>
#include <Cad3d_CurveOnSurfaceTools.hxx>

static Standard_Real DEFAULT_TOLERANCE = 1.0E-6;
static Standard_Real DEFAULT_PROXIMITY = 1.0E-3;
static Standard_Integer DEFAULT_NB_SAMPLES = 10;

using namespace AutLib;
using namespace CadLib;
using namespace GeoLib;

AutLib::CadLib::Cad3d_PairedOnSolid::Cad3d_PairedOnSolid()
	: theEdge0_(0)
	, theEdge1_(0)
{
}

AutLib::CadLib::Cad3d_PairedOnSolid::Cad3d_PairedOnSolid
(
	const Standard_Integer Index,
	const Global_Handle(Cad3d_EdgeOnSolid) Edge0,
	const Global_Handle(Cad3d_EdgeOnSolid) Edge1
)
	: Cad3d_EntityOnSolid(Index)
	, theEdge0_(Edge0)
	, theEdge1_(Edge1)
{
	theDiscretized_ = new Entity_PolyLine3d(Cad3d_CurveOnSurfaceTools::DiscretizedOf(*theEdge0_->CurveOnSurface(), DEFAULT_PROXIMITY, DEFAULT_TOLERANCE, DEFAULT_NB_SAMPLES));
}

AutLib::CadLib::Cad3d_PairedOnSolid::~Cad3d_PairedOnSolid()
{
	Clear();
}

void AutLib::CadLib::Cad3d_PairedOnSolid::Init
(
	const Standard_Integer Index,
	const Global_Handle(Cad3d_EdgeOnSolid) Edge0,
	const Global_Handle(Cad3d_EdgeOnSolid) Edge1
)
{
	Cad3d_EntityOnSolid::SetIndex(Index);

	theEdge0_ = Edge0;
	theEdge1_ = Edge1;

	theDiscretized_ = new Entity_PolyLine3d(Cad3d_CurveOnSurfaceTools::DiscretizedOf(*theEdge0_->CurveOnSurface(), DEFAULT_PROXIMITY, DEFAULT_TOLERANCE, DEFAULT_NB_SAMPLES));
}

void AutLib::CadLib::Cad3d_PairedOnSolid::SetEdge0(const Global_Handle(Cad3d_EdgeOnSolid) Edge)
{
	theEdge0_ = Edge;
}

void AutLib::CadLib::Cad3d_PairedOnSolid::SetEdge1(const Global_Handle(Cad3d_EdgeOnSolid) Edge)
{
	theEdge1_ = Edge;
}

void AutLib::CadLib::Cad3d_PairedOnSolid::Discrete(const Standard_Real Deflection)
{
	if (NOT theEdge0_) { THROW_STANDARD_EXCEPTION(" Null Edge"); }

	if (theDiscretized_) Clear();

	theDiscretized_ = new Entity_PolyLine3d(Cad3d_CurveOnSurfaceTools::DiscretizedOf(*theEdge0_->CurveOnSurface(), Deflection, DEFAULT_TOLERANCE, DEFAULT_NB_SAMPLES));
}

void AutLib::CadLib::Cad3d_PairedOnSolid::ExportToPlt(fstream & File) const
{
	if (theDiscretized_)
	{
		theDiscretized_->ExportToPlt(File);
	}
}

void AutLib::CadLib::Cad3d_PairedOnSolid::Clear()
{
	FreePointer(theDiscretized_);
}