#include <Duct_XParameters.hxx>

#include <Duct_ConstParameters.hxx>

AutLib::CadLib::Duct_XParameters::Duct_XParameters()
{
}

void AutLib::CadLib::Duct_XParameters::AllocateMemory(const Standard_Integer nbSections)
{
	if (NOT INSIDE(nbSections, Duct_ConstParameters::MinNbSections(), Duct_ConstParameters::MaxNbSections()))
	{
		THROW_STANDARD_EXCEPTION(" Invalid Nb of Sections");
	}

	xXCoords_.Resize(nbSections);
	xYCoords_.Resize(nbSections);
	xZCoords_.Resize(nbSections);

	xUpperTightness_.Resize(nbSections);
	xLowerTightness_.Resize(nbSections);
	xSideSlope_.Resize(nbSections);
	xDepth_.Resize(nbSections);
	xWidth_.Resize(nbSections);
}