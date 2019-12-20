#include <Entity_TetrahedralizationTools.hxx>

#include <Geometry_Tools.hxx>
#include <Entity_Tetrahedralization.hxx>
#include <TColEntity_BasicQueueOfTetrahedronIndex.hxx>

using namespace AutLib;
using namespace GeoLib;

void AutLib::GeoLib::Entity_TetrahedralizationTools::xCoord_Split
(
	const Standard_Real theX, 
	const Entity_Tetrahedralization & theTetrahedralization, 
	Entity_Tetrahedralization & theLeft, 
	Entity_Tetrahedralization & theRight
)
{
	Get_Const_Object(Coords) = theTetrahedralization.Points();
	Get_Const_Object(Tets) = theTetrahedralization.Tetrahedrons();

	TColEntity_BasicQueueOfTetrahedronIndex QLeft, QRight;
	forThose
	(
		Index,
		0, 
		MaxIndexOf(Tets)
	)
	{
		Get_Const_Object(Tetrahedron) = Tets[Index];

		Standard_Integer V0, V1, V2, V3;
		Tetrahedron.GetValue(V0, V1, V2, V3);

		Geom_Pnt3d Centre;
		Try_Exception_Handle_Exit(Centre = Geometry_Tools::CentreOfTetrahedron(Coords[Index_Of(V0)], Coords[Index_Of(V1)], Coords[Index_Of(V2)], Coords[Index_Of(V3)]));

		if (Centre.X() < theX) { QLeft.EnQueue(Tetrahedron); }
		else { QRight.EnQueue(Tetrahedron); }
	}

	theLeft.Points() = Coords;
	theRight.Points() = Coords;

	QLeft.RetrieveTo(theLeft.Tetrahedrons());
	QRight.RetrieveTo(theRight.Tetrahedrons());
}

void AutLib::GeoLib::Entity_TetrahedralizationTools::yCoord_Split
(
	const Standard_Real theY,
	const Entity_Tetrahedralization & theTetrahedralization,
	Entity_Tetrahedralization & theLeft,
	Entity_Tetrahedralization & theRight
)
{
	Get_Const_Object(Coords) = theTetrahedralization.Points();
	Get_Const_Object(Tets) = theTetrahedralization.Tetrahedrons();

	TColEntity_BasicQueueOfTetrahedronIndex QLeft, QRight;
	forThose
	(
		Index,
		0,
		MaxIndexOf(Tets)
	)
	{
		Get_Const_Object(Tetrahedron) = Tets[Index];

		Standard_Integer V0, V1, V2, V3;
		Tetrahedron.GetValue(V0, V1, V2, V3);

		Geom_Pnt3d Centre;
		Try_Exception_Handle_Exit(Centre = Geometry_Tools::CentreOfTetrahedron(Coords[Index_Of(V0)], Coords[Index_Of(V1)], Coords[Index_Of(V2)], Coords[Index_Of(V3)]));

		if (Centre.Y() < theY) { QLeft.EnQueue(Tetrahedron); }
		else { QRight.EnQueue(Tetrahedron); }
	}

	theLeft.Points() = Coords;
	theRight.Points() = Coords;

	QLeft.RetrieveTo(theLeft.Tetrahedrons());
	QRight.RetrieveTo(theRight.Tetrahedrons());
}

void AutLib::GeoLib::Entity_TetrahedralizationTools::zCoord_Split
(
	const Standard_Real theZ, 
	const Entity_Tetrahedralization & theTetrahedralization, 
	Entity_Tetrahedralization & theLeft,
	Entity_Tetrahedralization & theRight
)
{
	Get_Const_Object(Coords) = theTetrahedralization.Points();
	Get_Const_Object(Tets) = theTetrahedralization.Tetrahedrons();

	TColEntity_BasicQueueOfTetrahedronIndex QLeft, QRight;
	forThose
	(
		Index,
		0,
		MaxIndexOf(Tets)
	)
	{
		Get_Const_Object(Tetrahedron) = Tets[Index];

		Standard_Integer V0, V1, V2, V3;
		Tetrahedron.GetValue(V0, V1, V2, V3);

		Geom_Pnt3d Centre;
		Try_Exception_Handle_Exit(Centre = Geometry_Tools::CentreOfTetrahedron(Coords[Index_Of(V0)], Coords[Index_Of(V1)], Coords[Index_Of(V2)], Coords[Index_Of(V3)]));

		if (Centre.Z() < theZ) { QLeft.EnQueue(Tetrahedron); }
		else { QRight.EnQueue(Tetrahedron); }
	}

	theLeft.Points() = Coords;
	theRight.Points() = Coords;

	QLeft.RetrieveTo(theLeft.Tetrahedrons());
	QRight.RetrieveTo(theRight.Tetrahedrons());
}