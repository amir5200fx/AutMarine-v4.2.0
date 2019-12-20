#pragma once
inline
Standard_Integer AutLib::CadLib::Nurbs_Curve2d::MaxIndex() const
{
	return theMaxIndex_;
}

inline 
Standard_Integer AutLib::CadLib::Nurbs_Curve2d::Degree() const
{
	return theDeg_;
}

inline 
Standard_Integer AutLib::CadLib::Nurbs_Curve2d::NbPoles() const
{
	return thePoles_.Size();
}

inline
Standard_Real AutLib::CadLib::Nurbs_Curve2d::FirstParameter() const
{
	return 0;
}

inline 
Standard_Real AutLib::CadLib::Nurbs_Curve2d::LastParameter() const
{
	return 1;
}

inline 
const M_AUT TColStd_Ary1dOfReal & AutLib::CadLib::Nurbs_Curve2d::Weights() const
{
	return theWeights_;
}

inline 
const M_AUT TColStd_Ary1dOfReal & AutLib::CadLib::Nurbs_Curve2d::Knots() const
{
	return theKnots_;
}

inline 
const M_AUT TColGeom_Ary1dOfPnt2d & AutLib::CadLib::Nurbs_Curve2d::Poles() const
{
	return thePoles_;
}