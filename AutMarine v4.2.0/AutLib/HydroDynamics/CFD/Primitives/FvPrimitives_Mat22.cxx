#include <FvPrimitives_Mat22.hxx>

AutLib::FvLib::FvPrimitives_Mat22::FvPrimitives_Mat22()
{
	theValues_[0][0] = (Scalar)0;
	theValues_[0][1] = (Scalar)0;
	theValues_[1][0] = (Scalar)0;
	theValues_[1][1] = (Scalar)0;
}

AutLib::FvLib::FvPrimitives_Mat22::FvPrimitives_Mat22
(
	const Scalar theA00, 
	const Scalar theA01, 
	const Scalar theA10,
	const Scalar theA11
)
{
	theValues_[0][0] = theA00;
	theValues_[0][1] = theA01;
	theValues_[1][0] = theA10;
	theValues_[1][1] = theA11;
}

void AutLib::FvLib::FvPrimitives_Mat22::Init
(
	const Scalar theA00,
	const Scalar theA01, 
	const Scalar theA10, 
	const Scalar theA11
)
{
	theValues_[0][0] = theA00;
	theValues_[0][1] = theA01;
	theValues_[1][0] = theA10;
	theValues_[1][1] = theA11;
}