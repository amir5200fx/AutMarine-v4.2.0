#include <Entity_Box3d.hxx>

void AutLib::GeoLib::Entity_Box3d::Print(Standard_OStream & Ostream) const
{
	Ostream
		<< "P0 = ["
		<< theXmin_
		<< ","
		<< theYmin_
		<< ","
		<< theZmin_
		<< "],  P1 = ["
		<< theXmax_
		<< ","
		<< theYmax_
		<< ","
		<< theZmax_
		<< "]";
}