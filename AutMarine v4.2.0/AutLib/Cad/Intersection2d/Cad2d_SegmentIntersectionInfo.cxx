#include <Cad2d_SegmentIntersectionInfo.hxx>

#include <Cad2d_CurveOnPlane.hxx>

AutLib::CadLib::Cad2d_SegmentIntersectionInfo::Cad2d_SegmentIntersectionInfo()
{
}

AutLib::CadLib::Cad2d_SegmentIntersectionInfo::Cad2d_SegmentIntersectionInfo
(
	Global_Handle(Cad2d_CurveOnPlane) theCurve1, 
	Global_Handle(Cad2d_CurveOnPlane) theCurve2
)
	: theCurve1_(theCurve1)
	, theCurve2_(theCurve2)
{
}

AutLib::CadLib::Cad2d_SegmentIntersectionInfo::~Cad2d_SegmentIntersectionInfo()
{
}

void AutLib::CadLib::Cad2d_SegmentIntersectionInfo::Init
(
	Global_Handle(Cad2d_CurveOnPlane) theCurve1,
	Global_Handle(Cad2d_CurveOnPlane) theCurve2
)
{
	theCurve1_ = theCurve1;
	theCurve2_ = theCurve2;
}

void AutLib::CadLib::Cad2d_SegmentIntersectionInfo::ExportToPlt(fstream & File) const
{
	if (theCurve1_) theCurve1_->ExportToPlt(File);
	if (theCurve2_) theCurve2_->ExportToPlt(File);
}