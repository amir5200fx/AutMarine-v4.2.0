#pragma once
inline
Standard_Real AutLib::MeshLib::SizeMap2d_ModifyBackSize::ElementSize(const Mesh2d_Edge & Edge) const
{
	Standard_Real h1 = SizeMap2d_StdBackSize::ElementSize(Edge.Centre());
	Standard_Real h2 = SizeMap2d_StdBackSize::ElementSize(CalcOptimumPoint(h1, Edge));

	if (h2 >= h1)
		return h2;
	else
	{
		Standard_Real Fraction = (h1 - h2) / h1;

		if (Fraction <= theDelta_)
			return h1;
		else
			return theCoeff_*h1 + (1.0 - theCoeff_)*h2;
	}
}
