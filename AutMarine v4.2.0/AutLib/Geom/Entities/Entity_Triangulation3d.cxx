#include <Entity_Triangulation3d.hxx>

#include <Entity_Box3d.hxx>
#include <Entity_StaticChain3d.hxx>
#include <IO_Tecplot.hxx>

using namespace AutLib;
using namespace GeoLib;

AutLib::GeoLib::Entity_Triangulation3d::Entity_Triangulation3d()
{
}

AutLib::GeoLib::Entity_Triangulation3d::Entity_Triangulation3d
(
	const TColGeom_Ary1dOfPnt3d & Coords, 
	const TColEntity_Ary1dOfTriangleIndex & Triangles
)
	: thePoints_(Coords)
	, theTriangles_(Triangles)
{
}

Entity_Box3d AutLib::GeoLib::Entity_Triangulation3d::BoundingBox() const
{
	Entity_Box3d Box;

	Standard_Real
		Xp,
		Yp,
		Zp;

	Get_Const_Object(Coords) = thePoints_;

	Try_Exception_Handle_Exit(Box.Xmax() = Box.Xmin() = Coords[0].X());
	Try_Exception_Handle_Exit(Box.Ymax() = Box.Ymin() = Coords[0].Y());
	Try_Exception_Handle_Exit(Box.Zmax() = Box.Zmin() = Coords[0].Z());

	forThose
	(
		Index,
		1,
		MaxIndexOf(Coords)
	)
	{
		Xp = Coords[Index].X();
		Yp = Coords[Index].Y();
		Zp = Coords[Index].Z();

		if (Xp < Box.Xmin()) Box.Xmin() = Xp;
		if (Xp > Box.Xmax()) Box.Xmax() = Xp;
		if (Yp < Box.Ymin()) Box.Ymin() = Yp;
		if (Yp > Box.Ymax()) Box.Ymax() = Yp;
		if (Zp < Box.Zmin()) Box.Zmin() = Zp;
		if (Zp > Box.Zmax()) Box.Zmax() = Zp;
	}

	MOVE(Box);
}

void AutLib::GeoLib::Entity_Triangulation3d::Reverse()
{
	forThose(Index, 0, MaxIndexOf(theTriangles_))
		SWAP(theTriangles_[Index].V0(), theTriangles_[Index].V2());
}

void AutLib::GeoLib::Entity_Triangulation3d::ImportFrom(fstream & File)
{
	Standard_String String;
	Standard_Integer NbPoints, NbElements;

	File >> String >> NbPoints;
	File >> String >> NbElements;

	thePoints_.Resize(NbPoints);
	theTriangles_.Resize(NbElements);

	forThose(Index, 0, MaxIndexOf(thePoints_))
		File >> thePoints_[Index];
	forThose(Index, 0, MaxIndexOf(theTriangles_))
		File >> theTriangles_[Index];
}

void AutLib::GeoLib::Entity_Triangulation3d::ExportTo(fstream & File) const
{
	File << "Nb_of_Points= " << thePoints_.Size() << endl;
	File << "Nb_of_Elements= " << theTriangles_.Size() << endl;
	forThose(Index, 0, MaxIndexOf(thePoints_))
		File << thePoints_[Index] << endl;
	forThose(Index, 0, MaxIndexOf(theTriangles_))
		File << theTriangles_[Index] << endl;
}

void AutLib::GeoLib::Entity_Triangulation3d::ExportToPlt(fstream & File) const
{
	M_IO IO_TecPlot::ExportMesh(thePoints_, theTriangles_, File);
}

void AutLib::GeoLib::Entity_Triangulation3d::ExportNormalsToPlt(fstream & File) const
{
	Entity_StaticChain3d Chain;
	Get_Object(Coords) = Chain.Coords();
	Get_Object(Edges) = Chain.Edges();

	Coords.Resize(2 * theTriangles_.Size());
	Edges.Resize(theTriangles_.Size());

	Standard_Integer K = 0;
	forThose
	(
		Index,
		0, 
		MaxIndexOf(theTriangles_)
	)
	{
		Get_Const_Object(Triangle) = theTriangles_.Value(Index);

		Standard_Integer V1 = Index_Of(Triangle.V0());
		Standard_Integer V2 = Index_Of(Triangle.V1());
		Standard_Integer V3 = Index_Of(Triangle.V2());

		Geom_Pnt3d P1 = thePoints_.Value(V1);
		Geom_Pnt3d P2 = thePoints_.Value(V2);
		Geom_Pnt3d P3 = thePoints_.Value(V3);

		Standard_Real L = DistanceSQ(P1, P2);
		L = MAX(L, DistanceSQ(P2, P3));
		L = MAX(L, DistanceSQ(P3, P1));

		Geom_Pnt3d Pt = (P1 + P2 + P3) / 3.0;

		Geom_Pnt3d Pn = CrossProduct(P2 - P1, P3 - P1).UnitLength();
		Pn *= sqrt(L);

		Coords.SetValue(K, Pt);
		K++;

		Coords.SetValue(K, Pt + Pn);
		K++;

		Edges.SetValue(Index, Entity_EdgeIndex(K - 1, K));
	}

	Chain.ExportToPlt(File);
}