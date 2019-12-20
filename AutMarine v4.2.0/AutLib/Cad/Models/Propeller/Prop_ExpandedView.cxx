#include <Prop_ExpandedView.hxx>

AutLib::CadLib::Prop_ExpandedView::Prop_ExpandedView(const Standard_Integer theNbSegments)
	: theX_(theNbSegments)
	, theXS_(theNbSegments)
	, theTF_(theNbSegments)
	, theTB_(theNbSegments)
	, theYF_(theNbSegments)
	, theYB_(theNbSegments)
{
}