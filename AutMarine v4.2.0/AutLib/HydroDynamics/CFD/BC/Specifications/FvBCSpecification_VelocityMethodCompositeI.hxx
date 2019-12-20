#pragma once
inline
Standard_Real AutLib::FvLib::FvBCSpecification_VelocityMethodComposite::xValue(const Geom_Pnt2d & theCoord) const
{
	return theXComponent_.Value(theCoord);
}

inline 
Standard_Real AutLib::FvLib::FvBCSpecification_VelocityMethodComposite::yValue(const Geom_Pnt2d & theCoord) const
{
	return theYComponent_.Value(theCoord);
}

inline 
Vec2 AutLib::FvLib::FvBCSpecification_VelocityMethodComposite::Value(const Geom_Pnt2d & theCoord) const
{
	return Vec2(theXComponent_.Value(theCoord), theYComponent_.Value(theCoord));
}