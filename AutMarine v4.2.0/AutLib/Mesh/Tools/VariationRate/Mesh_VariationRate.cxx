#include <Mesh_VariationRate.hxx>

static const Standard_Real DEFAULT_VERYLOWRATE = 0.1;
static const Standard_Real DEFAULT_LOWRATE = 0.2;
static const Standard_Real DEFAULT_MODERATE = 0.35;
static const Standard_Real DEFAULT_FASTRATE = 0.5;

Standard_Real AutLib::MeshLib::Mesh_VariationRate::VeryLowrate()
{
	return DEFAULT_VERYLOWRATE;
}

Standard_Real AutLib::MeshLib::Mesh_VariationRate::Lowrate()
{
	return DEFAULT_LOWRATE;
}

Standard_Real AutLib::MeshLib::Mesh_VariationRate::Moderate()
{
	return DEFAULT_MODERATE;
}

Standard_Real AutLib::MeshLib::Mesh_VariationRate::Highrate()
{
	return DEFAULT_FASTRATE;
}

Standard_Real AutLib::MeshLib::Mesh_VariationRate::Rate(const Mesh_VariationRateInfo Info)
{
	switch (Info)
	{
	case Mesh_VariationRateInfo_VerySLOW:
		return VeryLowrate();
	case Mesh_VariationRateInfo_SLOW:
		return Lowrate();
	case Mesh_VariationRateInfo_MODERATE:
		return Moderate();
	case Mesh_VariationRateInfo_FAST:
		return Highrate();
	}

	return Moderate();
}