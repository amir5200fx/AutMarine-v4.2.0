#include <SizeMap3d_UniSize.hxx>

AutLib::MeshLib::SizeMap3d_UniSize::SizeMap3d_UniSize(const Standard_Real Size)
	: theSize_(Size)
{
	THROW_STANDARD_EXCEPTION_IF(theSize_ EQUAL 0, "Invalid Size");
	theInvSize_ = 1.0 / theSize_;
}