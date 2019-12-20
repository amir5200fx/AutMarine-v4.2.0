#include <Mesh3d_Ship.hxx>

#include <Compound_Ship.hxx>
#include <Mesh_ReferenceValues.hxx>
#include <Mesh3d_Region.hxx>

using namespace AutLib;
using namespace CadLib;

AutLib::MeshLib::Mesh3d_Ship::Mesh3d_Ship()
	: theReference_(NULL)
	, theRegion_(NULL)
	, theShip_(NULL)
{
	theShip_ = new Compound_Ship;
}

AutLib::MeshLib::Mesh3d_Ship::~Mesh3d_Ship()
{
	FreePointer(theReference_);
	FreePointer(theRegion_);
	FreePointer(theShip_);
}

void AutLib::MeshLib::Mesh3d_Ship::Init()
{
	theShip_->Make();


}

void AutLib::MeshLib::Mesh3d_Ship::Perform()
{

}