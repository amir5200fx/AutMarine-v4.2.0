#include <Cad2d_IntersectionInfo.hxx>

#include <Cad2d_CurveOnPlane.hxx>
#include <Cad2d_PointIntersectionInfo.hxx>
#include <Cad2d_SegmentIntersectionInfo.hxx>

AutLib::CadLib::Cad2d_IntersectionInfo::Cad2d_IntersectionInfo()
{
}

AutLib::CadLib::Cad2d_IntersectionInfo::Cad2d_IntersectionInfo
(
	const TColCad2d_HAry1dOfPointIntersectionInfo & thePoints,
	const TColCad2d_HAry1dOfSegmentIntersectionInfo & theSegments
)
	: thePoints_(thePoints)
	, theSegments_(theSegments)
{
}

AutLib::CadLib::Cad2d_IntersectionInfo::~Cad2d_IntersectionInfo()
{
	FreeMemory(thePoints_);
	FreeMemory(theSegments_);
}

void AutLib::CadLib::Cad2d_IntersectionInfo::Init
(
	const TColCad2d_HAry1dOfPointIntersectionInfo & thePoints,
	const TColCad2d_HAry1dOfSegmentIntersectionInfo & theSegments
)
{
	thePoints_ = thePoints;
	theSegments_ = theSegments;
}

void AutLib::CadLib::Cad2d_IntersectionInfo::ExportToPlt(fstream & File) const
{
	forThose
	(
		Index,
		0, 
		MaxIndexOf(thePoints_)
	)
	{
		Debug_Null_Pointer(thePoints_[Index]);
		thePoints_[Index]->ExportToPlt(File);
	}

	forThose
	(
		Index,
		0, 
		MaxIndexOf(theSegments_)
	)
	{
		Debug_Null_Pointer(theSegments_[Index]);
		theSegments_[Index]->ExportToPlt(File);
	}
}