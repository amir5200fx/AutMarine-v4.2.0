#pragma once
inline
Standard_Real AutLib::MeshLib::SizeMap3d_ModifyBackSize::ElementSize(const Mesh3d_Facet & theFacet) const
{
	Standard_Real h1 = SizeMap3d_StdBackSize::ElementSize(theFacet.Centre());
	Standard_Real h2 = SizeMap3d_StdBackSize::ElementSize(CalcOptimumCoord(h1, theFacet));

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