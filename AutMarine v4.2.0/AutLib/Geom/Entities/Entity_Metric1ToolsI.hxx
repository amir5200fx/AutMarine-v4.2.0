#pragma once

inline
M_GEO Entity_Metric1 AutLib::GeoLib::Entity_Metric1Tools::InterpolationIM1
(
	const Standard_Real c1, 
	const Standard_Real c2, 
	const Standard_Real c3, 
	const Entity_Metric1 & M1, 
	const Entity_Metric1 & M2, 
	const Entity_Metric1 & M3
)
{
	return Entity_Metric1
	(
		c1*M1.A() + c2*M2.A() + c3*M3.A(),
		c1*M1.B() + c2*M2.B() + c3*M3.B(), 
		c1*M1.C() + c2*M2.C() + c3*M3.C()
	);
}