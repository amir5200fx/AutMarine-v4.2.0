#include <FvReferences_Info.hxx>

Vec2 AutLib::FvLib::FvReferences_Info::Gravity()
{
	return Vec2(0, -9.806);
}

Scalar AutLib::FvLib::FvReferences_Info::Pressure()
{
	return (Scalar)101325.0;
}