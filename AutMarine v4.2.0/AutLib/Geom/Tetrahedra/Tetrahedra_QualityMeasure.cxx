#include <Tetrahedra_QualityMeasureParameters.hxx>

#include <Tetrahedra_QualityMeasure.hxx>

AutLib::GeoLib::Tetrahedra_QualityMeasure::Tetrahedra_QualityMeasure()
{
}

Standard_Real AutLib::GeoLib::Tetrahedra_QualityMeasure::CalcMinSineQuality
(
	const Geom_Pnt3d & theP0,
	const Geom_Pnt3d & theP1,
	const Geom_Pnt3d & theP2,
	const Geom_Pnt3d & theP3
) const
{
	theParameters_.Init(theP0, theP1, theP2, theP3);

	if (theParameters_.Volume() < EPS6) { return 0; }

	Standard_Real minQuality = RealLast();

	if (theParameters_.squareArea2() > 0 AND theParameters_.squareArea3() > 0)
	{
		Standard_Real Sine2 = theParameters_.squareL01() / (theParameters_.squareArea2()*theParameters_.squareArea3());
		if (Sine2 < minQuality)
		{
			minQuality = Sine2;
		}
	}
	else { return 0; }

	if (theParameters_.squareArea0() > 0 AND theParameters_.squareArea3() > 0)
	{
		Standard_Real Sine2 = theParameters_.squareL12() / (theParameters_.squareArea0()*theParameters_.squareArea3());
		if (Sine2 < minQuality)
		{
			minQuality = Sine2;
		}
	}
	else { return 0; }

	if (theParameters_.squareArea1() > 0 AND theParameters_.squareArea3() > 0)
	{
		Standard_Real Sine2 = theParameters_.squareL02() / (theParameters_.squareArea1()*theParameters_.squareArea3());
		if (Sine2 < minQuality)
		{
			minQuality = Sine2;
		}
	}
	else { return 0; }

	if (theParameters_.squareArea1() > 0 AND theParameters_.squareArea2() > 0)
	{
		Standard_Real Sine2 = theParameters_.squareL03() / (theParameters_.squareArea1()*theParameters_.squareArea2());
		if (Sine2 < minQuality)
		{
			minQuality = Sine2;
		}
	}
	else { return 0; }

	if (theParameters_.squareArea0() > 0 AND theParameters_.squareArea2() > 0)
	{
		Standard_Real Sine2 = theParameters_.squareL13() / (theParameters_.squareArea0()*theParameters_.squareArea2());
		if (Sine2 < minQuality)
		{
			minQuality = Sine2;
		}
	}
	else { return 0; }

	if (theParameters_.squareArea0() > 0 AND theParameters_.squareArea1() > 0)
	{
		Standard_Real Sine2 = theParameters_.squareL23() / (theParameters_.squareArea0()*theParameters_.squareArea1());
		if (Sine2 < minQuality)
		{
			minQuality = Sine2;
		}
	}
	else { return 0; }

	return sqrt(minQuality)*theParameters_.Volume();
}