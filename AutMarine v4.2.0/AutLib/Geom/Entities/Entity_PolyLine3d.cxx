#include <Entity_PolyLine3d.hxx>

#include <IO_Tecplot.hxx>

AutLib::GeoLib::Entity_PolyLine3d::Entity_PolyLine3d()
	: theDeflection_(0)
{
}

AutLib::GeoLib::Entity_PolyLine3d::Entity_PolyLine3d(const TColGeom_Ary1dOfPnt3d & thePoints)
	: thePoints_(thePoints)
	, theDeflection_(0)
{
}

void AutLib::GeoLib::Entity_PolyLine3d::Init(const TColGeom_Ary1dOfPnt3d & thePoints)
{
	thePoints_ = thePoints;
}

void AutLib::GeoLib::Entity_PolyLine3d::SetDeflection(const Standard_Real D)
{
	theDeflection_ = D;
}

void AutLib::GeoLib::Entity_PolyLine3d::SetCoords(const TColGeom_Ary1dOfPnt3d & Points)
{
	thePoints_ = Points;
}

void AutLib::GeoLib::Entity_PolyLine3d::Reverse()
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

void AutLib::GeoLib::Entity_PolyLine3d::Smoothing
(
	const Standard_Real Omega, 
	const Standard_Integer NbIterations
)
{
	forThose(Iter, 1, NbIterations)
	{
		forThose(Index, 1, MaxIndexOf(thePoints_) - 1)
		{
			Geom_Pnt3d DP = MEAN(thePoints_[Index - 1], thePoints_[Index + 1]) - thePoints_[Index];
			thePoints_[Index] += Omega*DP;
		}
	}
}

void AutLib::GeoLib::Entity_PolyLine3d::ExportToPlt(fstream & File) const
{
	M_IO IO_TecPlot::ExportCurve(thePoints_, File);
}