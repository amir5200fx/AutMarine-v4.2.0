#include <Entity_Polygon2d.hxx>

#include <Entity_Triangulation2d.hxx>
#include <IO_Tecplot.hxx>
#include <TColEntity_Ary1dOfTriangleIndex.hxx>

AutLib::GeoLib::Entity_Polygon2d::Entity_Polygon2d()
	: theDeflection_(0)
{
}

AutLib::GeoLib::Entity_Polygon2d::Entity_Polygon2d(const TColGeom_Ary1dOfPnt2d & Points)
	: thePoints_(Points)
	, theDeflection_(0)
{
}

void AutLib::GeoLib::Entity_Polygon2d::Init(const TColGeom_Ary1dOfPnt2d & Points)
{
	thePoints_ = Points;
}

void AutLib::GeoLib::Entity_Polygon2d::SetDeflection(const Standard_Real D)
{
	theDeflection_ = D;
}

void AutLib::GeoLib::Entity_Polygon2d::SetCoords(const TColGeom_Ary1dOfPnt2d & Points)
{
	thePoints_ = Points;
}

void AutLib::GeoLib::Entity_Polygon2d::Reverse()
{
	Standard_Integer Imax = MaxIndexOf(thePoints_);
	forThose
	(
		Index,
		0, 
		thePoints_.Size() / 2 - 1
	)
	{
		SWAP(thePoints_[Index], thePoints_[Imax - Index]);
	}
}

void AutLib::GeoLib::Entity_Polygon2d::Smoothing
(
	const Standard_Real Omega,
	const Standard_Integer NbIterations
)
{
	forThose(Iter, 1, NbIterations)
	{
		forThose(Index, 1, MaxIndexOf(thePoints_) - 1)
		{
			Geom_Pnt2d DP = MEAN(thePoints_[Index - 1], thePoints_[Index + 1]) - thePoints_[Index];
			thePoints_[Index] += Omega*DP;
		}
	}
}

void AutLib::GeoLib::Entity_Polygon2d::ExportToPlt(fstream & File) const
{
	M_IO IO_TecPlot::ExportCurve(thePoints_, File);
}

void AutLib::GeoLib::Entity_Polygon2d::ExportToPlt
(
	const Primitive_Field & theField, 
	fstream & File
) const
{
	TColEntity_Ary1dOfTriangleIndex Triangles(thePoints_.Size() - 1);
	forThose(Index, 0, MaxIndexOf(Triangles))
	{
		Triangles[Index] = Entity_TriangleIndex(Index + 1, Index + 2, Index + 1);
	}
	Entity_Triangulation2d Mesh(thePoints_, Triangles);
	M_IO IO_TecPlot::ExportField(Mesh, theField, File);
}