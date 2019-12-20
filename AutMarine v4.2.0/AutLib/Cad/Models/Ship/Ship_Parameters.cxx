#include <Ship_Parameters.hxx>

AutLib::CadLib::Ship_Parameters::Ship_Parameters()
{
}

void AutLib::CadLib::Ship_Parameters::SetDimensions(const Ship_Dimensions & Dimension)
{
	Dimensions_ = Dimension;
}

void AutLib::CadLib::Ship_Parameters::SetTransomForm(const Ship_TransomForm & Transom)
{
	Transom_ = Transom;
}

void AutLib::CadLib::Ship_Parameters::SetStemForm(const Ship_StemForm & StemForm)
{
	Stem_ = StemForm;
}

void AutLib::CadLib::Ship_Parameters::SetHullForm(const Ship_HullForm & HullForm)
{
	Hull_ = HullForm;
}

void AutLib::CadLib::Ship_Parameters::SetKeelForm(const Ship_KeelForm & KeelForm)
{
	Keel_ = KeelForm;
}

AutLib::CadLib::Ship_Dimensions & AutLib::CadLib::Ship_Parameters::Dimensions()
{
	return Dimensions_;
}

AutLib::CadLib::Ship_TransomForm & AutLib::CadLib::Ship_Parameters::Transom()
{
	return Transom_;
}

AutLib::CadLib::Ship_StemForm & AutLib::CadLib::Ship_Parameters::Stem()
{
	return Stem_;
}

AutLib::CadLib::Ship_HullForm & AutLib::CadLib::Ship_Parameters::Hull()
{
	return Hull_;
}

AutLib::CadLib::Ship_KeelForm & AutLib::CadLib::Ship_Parameters::Keel()
{
	return Keel_;
}

const AutLib::CadLib::Ship_Dimensions & AutLib::CadLib::Ship_Parameters::Dimensions() const
{
	return Dimensions_;
}

const AutLib::CadLib::Ship_TransomForm & AutLib::CadLib::Ship_Parameters::Transom() const
{
	return Transom_;
}

const AutLib::CadLib::Ship_StemForm & AutLib::CadLib::Ship_Parameters::Stem() const
{
	return Stem_;
}

const AutLib::CadLib::Ship_HullForm & AutLib::CadLib::Ship_Parameters::Hull() const
{
	return Hull_;
}

const AutLib::CadLib::Ship_KeelForm & AutLib::CadLib::Ship_Parameters::Keel() const
{
	return Keel_;
}