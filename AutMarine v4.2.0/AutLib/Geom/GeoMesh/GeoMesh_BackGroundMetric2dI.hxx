#pragma once
#include <IO_Tecplot.hxx>
inline 
M_GEO Entity_Metric1 AutLib::GeoLib::GeoMesh_BackGroundMetric2d::MetricAt(const Geom_Pnt2d & Coord) const
{
	Standard_Boolean Sense;
	Entity_Metric1 Metric = MetricAt(Coord, Sense);

	if (NOT Sense)
	{
		THROW_STANDARD_EXCEPTION(" Element not found");
		return Entity_Metric1();
	}
	MOVE(Metric);
}

inline
M_GEO Entity_Metric1 AutLib::GeoLib::GeoMesh_BackGroundMetric2d::MetricAt
(
	const Geom_Pnt2d & theCoord,
	Standard_Boolean & Sense
) const
{
	Global_Handle(Entity_Element2d) ElementPtr = theMesh_.TriangleLocation(theCurrentElement_, theCoord);

	if (NOT ElementPtr)
	{
		/*cout << theCoord << endl;
		Open_OutputFile_TecPlot(Plot, "test");
		theMesh_.ExportToPlt(Plot);
		M_IO IO_TecPlot::ExportPoint(theCoord, Plot);*/
		Sense = Standard_False;
		return Entity_Metric1();
	}

	theCurrentElement_ = ElementPtr;

	const Entity_Element2d& Element = *ElementPtr;

	Standard_Real A1 = Geometry_Tools::AreaOfTriangle(Element.Node1()->Coord(), Element.Node2()->Coord(), theCoord);
	Standard_Real A2 = Geometry_Tools::AreaOfTriangle(Element.Node2()->Coord(), Element.Node0()->Coord(), theCoord);
	Standard_Real A3 = Geometry_Tools::AreaOfTriangle(Element.Node0()->Coord(), Element.Node1()->Coord(), theCoord);
	Standard_Real At = A1 + A2 + A3;

	A1 /= At;
	A2 /= At;
	A3 /= At;

	/*const Entity_Metric1& H1 = theSources_[Index_Of(Element.Node0()->Index())].Inversed();
	const Entity_Metric1& H2 = theSources_[Index_Of(Element.Node1()->Index())].Inversed();
	const Entity_Metric1& H3 = theSources_[Index_Of(Element.Node2()->Index())].Inversed();*/

	const Entity_Metric1& H1 = theSources_[Index_Of(Element.Node0()->Index())];
	const Entity_Metric1& H2 = theSources_[Index_Of(Element.Node1()->Index())];
	const Entity_Metric1& H3 = theSources_[Index_Of(Element.Node2()->Index())];
	/*H1.Print();
	H2.Print();
	H3.Print();
	cout << A1 << "  " << A2 << "  " << A3 << endl;
	(A1*H1 + A2*H2 + A3*H3).Print();*/
	//PAUSE;
	Sense = Standard_True;

	return A1*H1 + A2*H2 + A3*H3;
	//return (A1*H1 + A2*H2 + A3*H3).Inversed();
}

inline 
M_AUT TColEntity_Ary1dOfMetric1 & AutLib::GeoLib::GeoMesh_BackGroundMetric2d::Sources() const
{
	return theSources_;
}

inline 
M_GEO GeoMesh_TriangleMesh2d & AutLib::GeoLib::GeoMesh_BackGroundMetric2d::Mesh()
{
	return theMesh_;
}

inline 
const M_GEO GeoMesh_TriangleMesh2d & AutLib::GeoLib::GeoMesh_BackGroundMetric2d::Mesh() const
{
	return theMesh_;
}

inline 
const Global_Handle(M_GEO Entity_Box2d) AutLib::GeoLib::GeoMesh_BackGroundMetric2d::BoundingBox() const
{
	return theBoundingBox_;
}