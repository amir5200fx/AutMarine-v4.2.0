#pragma once
inline
void AutLib::CadLib::Ship_Profiles::SetFlare(Standard_Integer Index, const Ship_ShipParameterProfile & Flare)
{
	Try_Exception_Handle_Exit(theFlare_[Index] = Flare);
}

inline 
void AutLib::CadLib::Ship_Profiles::SetSkeg(Standard_Integer Index, const Ship_ShipParameterProfile & Skeg)
{
	Try_Exception_Handle_Exit(theSkeg_[Index] = Skeg);
}

inline 
void AutLib::CadLib::Ship_Profiles::SetSection(Standard_Integer Index, const Ship_ShipParameterProfile & Section)
{
	Try_Exception_Handle_Exit(theSection_[Index] = Section);
}

inline 
void AutLib::CadLib::Ship_Profiles::SetDeck(const Ship_ShipParameterProfile & Deck)
{
	theDeck_ = Deck;
}

inline 
void AutLib::CadLib::Ship_Profiles::SetButtock(const Ship_ShipParameterProfile & Buttock)
{
	theButtock_ = Buttock;
}

inline 
const M_AUT Ship_ShipParameterProfile & AutLib::CadLib::Ship_Profiles::Flare(Standard_Integer Index) const
{
	Debug_Bad_Index_Array1(Index, theFlare_);
	return theFlare_[Index];
}

inline 
const M_AUT Ship_ShipParameterProfile & AutLib::CadLib::Ship_Profiles::Skeg(Standard_Integer Index) const
{
	Debug_Bad_Index_Array1(Index, theSkeg_);
	return theSkeg_[Index];
}

inline 
const M_AUT Ship_ShipParameterProfile & AutLib::CadLib::Ship_Profiles::Section(Standard_Integer Index) const
{
	Debug_Bad_Index_Array1(Index, theSection_);
	return theSection_[Index];
}

inline 
const M_AUT Ship_ShipParameterProfile & AutLib::CadLib::Ship_Profiles::Deck() const
{
	return theDeck_;
}

inline 
const M_AUT Ship_ShipParameterProfile & AutLib::CadLib::Ship_Profiles::Buttock() const
{
	return theButtock_;
}