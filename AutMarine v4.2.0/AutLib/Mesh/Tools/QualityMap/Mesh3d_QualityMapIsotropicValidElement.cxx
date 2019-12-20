#include <Mesh3d_QualityMapIsotropicValidElement.hxx>

#include <Geometry_Tools.hxx>

using namespace AutLib;
using namespace GeoLib;

static const Standard_Real DEFAULT_TOLERANCE = 1.0E-6;

AutLib::MeshLib::Mesh3d_QualityMapIsotropicValidElement::Mesh3d_QualityMapIsotropicValidElement()
	: theTolerance_(DEFAULT_TOLERANCE)
{
}

Standard_Real AutLib::MeshLib::Mesh3d_QualityMapIsotropicValidElement::CalcQuality
(
	const Geom_Pnt3d & theP0,
	const Geom_Pnt3d & theP1, 
	const Geom_Pnt3d & theP2, 
	const Geom_Pnt3d & theP3
) const
{
	Standard_Real Vol = Geometry_Tools::Oriented(theP0, theP2, theP1, theP3);
	if (Vol < 0) Vol = 0;
	return Vol;
}

Standard_Real AutLib::MeshLib::Mesh3d_QualityMapIsotropicValidElement::GetInitialAlpha
(
	const TColMesh3d_HAry1dOfOptTetInfo & incidenttets,
	const Geom_Pnt3d & d,
	const Standard_Real r, 
	const Standard_Real RateEpsilon, 
	const Standard_Real theWorst
) const
{
	THROW_STANDARD_EXCEPTION("It's a virtual function");
	return 0;
}

void AutLib::MeshLib::Mesh3d_QualityMapIsotropicValidElement::GetActiveSet
(
	const TColMesh3d_HAry1dOfOptTetInfo & incidenttets, 
	const Standard_Real theActiveSetFactor, 
	const Standard_Real theWorst, 
	TColGeom_Ary1dOfPnt3d & theActiveGrads
) const
{
	THROW_STANDARD_EXCEPTION("It's a virtual function");
}

void AutLib::MeshLib::Mesh3d_QualityMapIsotropicValidElement::CalcOptInfo(const Global_Handle(Mesh3d_Node) theNode, Mesh3d_OptTetInfo & theTet) const
{
	THROW_STANDARD_EXCEPTION("It's a virtual function");
}