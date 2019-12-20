#include <Merge_Merge3dParameter.hxx>

AutLib::GeoLib::Merge_Merge3dParameter::Merge_Merge3dParameter()
	: theXmin_(RealFirst())
	, theYmin_(RealFirst())
	, theZmin_(RealFirst())
	, theDelta_(0)
	, theMaxIndex_(0)
{
}