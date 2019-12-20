#include <Entity_Element3d.hxx>

#include <Geometry_Tools.hxx>

using namespace AutLib;
using namespace GeoLib;

void AutLib::GeoLib::Entity_Element3d::CalcVolume()
{
	theVolume_ = Geometry_Tools::VolumeOfTetrahedron(Node0()->Coord(), Node1()->Coord(), Node2()->Coord(), Node3()->Coord());

	thel_ = pow(theVolume_, 1.0 / 3.0);
}