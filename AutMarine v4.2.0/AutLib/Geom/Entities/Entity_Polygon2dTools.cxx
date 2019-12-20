#include <Entity_Polygon2dTools.hxx>

#include <Entity_Polygon2d.hxx>
#include <Entity_Box2d.hxx>
#include <Entity_StaticChain2d.hxx>
#include <Entity_EdgeIndexTools.hxx>
#include <Geometry_Tools.hxx>
#include <Geometry_Distance.hxx>
#include <Geometry_Intersect.hxx>
#include <TColGeom_BasicQueueOfPnt2d.hxx>

using namespace AutLib;
using namespace GeoLib;

Entity_Box2d AutLib::GeoLib::Entity_Polygon2dTools::BoundingBox(const Entity_Polygon2d & ThePolygon)
{
	Standard_Real Xmin, Xmax, Ymin, Ymax;
	Try_Exception_Handle_Exit(Geometry_Tools::CalcMinMax(ThePolygon.Points(), Xmin, Xmax, Ymin, Ymax));

	return Entity_Box2d(Xmin, Xmax, Ymin, Ymax);
}

Entity_StaticChain2d AutLib::GeoLib::Entity_Polygon2dTools::GetChain(const Entity_Polygon2d & thePolygon)
{
	Entity_StaticChain2d Chain;
	Chain.Init(thePolygon.Points(), Entity_EdgeIndexTools::OrderedList(thePolygon.NbPoints()));

	MOVE(Chain);
}