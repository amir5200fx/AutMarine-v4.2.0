#include <Ship_Dimensions.hxx>

#include <Ship_ConstParameters.hxx>

AutLib::CadLib::Ship_Dimensions::Ship_Dimensions()
{
}

void AutLib::CadLib::Ship_Dimensions::SetDraft(const Standard_Real Value)
{
	Set_ShipParameterValue
	(
		Value,
		Ship_ConstParameters::MinDraft(),
		Ship_ConstParameters::MaxDraft(),
		theDraft_
	);
}

void AutLib::CadLib::Ship_Dimensions::SetTransonHeight(const Standard_Real Value)
{
	Set_ShipParameterValue
	(
		Value,
		Ship_ConstParameters::MinTransomHeight(),
		Ship_ConstParameters::MaxTransomHeight(),
		theTransomHeight_
	);
}

void AutLib::CadLib::Ship_Dimensions::SetDepthAtBow(const Standard_Real Value)
{
	Set_ShipParameterValue
	(
		Value,
		Ship_ConstParameters::MinDepth(),
		Ship_ConstParameters::MaxDepth(),
		theDepthAtBow_
	);
}

void AutLib::CadLib::Ship_Dimensions::SetDepthAtTransom(const Standard_Real Value)
{
	Set_ShipParameterValue
	(
		Value,
		Ship_ConstParameters::MinDepth(),
		Ship_ConstParameters::MaxDepth(),
		theDepthAtTransom_
	);
}

void AutLib::CadLib::Ship_Dimensions::SetBeamOnDeck(const Standard_Real Value)
{
	Set_ShipParameterValue
	(
		Value,
		Ship_ConstParameters::MinBreadth(),
		Ship_ConstParameters::MaxBreadth(),
		theBeamOnDeck_
	);
}

void AutLib::CadLib::Ship_Dimensions::SetLengthOnDeck(const Standard_Real Value)
{
	Set_ShipParameterValue
	(
		Value,
		Ship_ConstParameters::MinLength(),
		Ship_ConstParameters::MaxLength(),
		theLenghtOnDeck_
	);
}

void AutLib::CadLib::Ship_Dimensions::SetNbNetRows(const Standard_Integer Value)
{
	Set_ShipParameterValue
	(
		Value,
		Ship_ConstParameters::MinNbRows(),
		Ship_ConstParameters::MaxNbRows(),
		theNbNetRows_
	);
}

void AutLib::CadLib::Ship_Dimensions::SetNbNetColumns(const Standard_Integer Value)
{
	Set_ShipParameterValue
	(
		Value,
		Ship_ConstParameters::MinNbSections(),
		Ship_ConstParameters::MaxNbSections(),
		theNbNetColumns_
	);
}

Standard_Real AutLib::CadLib::Ship_Dimensions::Draft() const
{
	return theDraft_;
}

Standard_Real AutLib::CadLib::Ship_Dimensions::TransomHeight() const
{
	return theTransomHeight_;
}

Standard_Real AutLib::CadLib::Ship_Dimensions::DepthAtBow() const
{
	return theDepthAtBow_;
}

Standard_Real AutLib::CadLib::Ship_Dimensions::DepthAtTransom() const
{
	return theDepthAtTransom_;
}

Standard_Real AutLib::CadLib::Ship_Dimensions::BeamOnDeck() const
{
	return theBeamOnDeck_;
}

Standard_Real AutLib::CadLib::Ship_Dimensions::LengthOnDeck() const
{
	return theLenghtOnDeck_;
}

Standard_Integer AutLib::CadLib::Ship_Dimensions::NbNetRows() const
{
	return theNbNetRows_;
}

Standard_Integer AutLib::CadLib::Ship_Dimensions::NbNetColumns() const
{
	return theNbNetColumns_;
}