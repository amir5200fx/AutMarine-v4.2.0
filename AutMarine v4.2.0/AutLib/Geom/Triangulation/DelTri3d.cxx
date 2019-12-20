#include <DelTri3d.hxx>

#include <Fade_3D.h>
#include <vector>

#include <Geometry_Tools.hxx>
#include <IO_TecPlot.hxx>

AutLib::GeoLib::DelTri3d::DelTri3d()
	: theInsertedPoints_(0)
{
}

AutLib::GeoLib::DelTri3d::DelTri3d(const TColGeom_Ary1dOfPnt3d & Points)
{
	theInsertedPoints_ = &Points;
}

void AutLib::GeoLib::DelTri3d::Import(const TColGeom_Ary1dOfPnt3d & Points)
{
	theInsertedPoints_ = &Points;
}

namespace AutLib
{
	namespace GeoLib
	{

		static inline Geom_Pnt3d ToPnt3d(const FADE3D::Point3 Point)
		{
			return Geom_Pnt3d(Point.x(), Point.y(), Point.z());
		}
	}
}

void AutLib::GeoLib::DelTri3d::Perform()
{
	if (IsNULL(theInsertedPoints_))
	{
		CloseProgram(" DelTri3d::Perform(), Found no Points");
	}

	Get_Const_Object(Coords) = *theInsertedPoints_;

	std::vector<FADE3D::Point3> Ipts;

	forThose
	(
		Index,
		0, 
		MaxIndexOf(Coords)
	)
	{
		Get_Const_Object(Point) = Coords[Index];

		Ipts.push_back(FADE3D::Point3(Point.X(), Point.Y(), Point.Z()));
	}

	FADE3D::Fade_3D Dt;

	Dt.insert(Ipts);

	std::vector<Global_Handle(FADE3D::Tet3)> vTets;
	std::vector<Global_Handle(FADE3D::Point3)> Vertices;

	Dt.getTetrahedra(vTets);
	Dt.getVertices(Vertices);
	
	thePts_.Resize((Standard_Integer)Vertices.size());
	theV_.Resize((Standard_Integer)vTets.size());
	theE_.Resize((Standard_Integer)vTets.size());

	forThose
	(
		Index,
		0, 
		MaxIndexOf(thePts_)
	)
	{
		Get_Object(Point) = *Vertices[Index];
		
		Point.customIndex = Index + 1;

		thePts_.SetValue
		(
			Index, 
			ToPnt3d(Point)
		);
	}

	forThose
	(
		Index,
		0, 
		MaxIndexOf(theV_)
	)
	{
		Get_Object(Tet) = *vTets[Index];

		Global_Handle(FADE3D::Point3) p0;
		Global_Handle(FADE3D::Point3) p1;
		Global_Handle(FADE3D::Point3) p2;
		Global_Handle(FADE3D::Point3) p3;

		Tet.getCorners(p0, p1, p2, p3);

		Tet.setCustomIndex(Index + 1);

		theV_.SetValue
		(
			Index, 
			Entity_TetrahedronIndex
			(
				p0->customIndex,
				p1->customIndex,
				p2->customIndex,
				p3->customIndex
			)
		);
	}

	forThose
	(
		Index,
		0,
		MaxIndexOf(theE_)
	)
	{
		Get_Object(Tet) = *vTets[Index];

		Global_Handle(FADE3D::Point3) p0;
		Global_Handle(FADE3D::Point3) p1;
		Global_Handle(FADE3D::Point3) p2;
		Global_Handle(FADE3D::Point3) p3;

		Tet.getCorners(p0, p1, p2, p3);

		Standard_Integer e0 = -1;
		Standard_Integer e1 = -1;
		Standard_Integer e2 = -1;
		Standard_Integer e3 = -1;

		if (Tet.getOppTet(p0)) e0 = Tet.getOppTet(p0)->getCustomIndex();
		if (Tet.getOppTet(p1)) e1 = Tet.getOppTet(p1)->getCustomIndex();
		if (Tet.getOppTet(p2)) e2 = Tet.getOppTet(p2)->getCustomIndex();
		if (Tet.getOppTet(p3)) e3 = Tet.getOppTet(p3)->getCustomIndex();

		theE_.SetValue
		(
			Index,
			Entity_TetrahedronIndex
			(
				e0,
				e1,
				e2,
				e3
			)
		);
	}
}

void AutLib::GeoLib::DelTri3d::ExportToPlt(fstream & File) const
{
	IoLib::IO_TecPlot::ExportMesh(thePts_, theV_, File);
}