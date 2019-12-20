#include <Prop_PropView.hxx>

AutLib::CadLib::Prop_PropView::Prop_PropView()
{
}

void AutLib::CadLib::Prop_PropView::AllocateMemory(const Standard_Integer theNbSections)
{
	theExpanded_.Resize(theNbSections);
	theWrapped_.Resize(theNbSections);
	theUnWrapped_.Resize(theNbSections);
}