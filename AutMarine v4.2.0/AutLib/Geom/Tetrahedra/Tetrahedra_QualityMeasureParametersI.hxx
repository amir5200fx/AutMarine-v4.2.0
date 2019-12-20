#pragma once
inline 
Standard_Real AutLib::GeoLib::Tetrahedra_QualityMeasureParameters::Volume() const
{
	return V_;
}

inline 
Standard_Real AutLib::GeoLib::Tetrahedra_QualityMeasureParameters::squareL03() const
{
	return lad_;
}

inline 
Standard_Real AutLib::GeoLib::Tetrahedra_QualityMeasureParameters::squareL13() const
{
	return lbd_;
}

inline 
Standard_Real AutLib::GeoLib::Tetrahedra_QualityMeasureParameters::squareL23() const
{
	return lcd_;
}

inline 
Standard_Real AutLib::GeoLib::Tetrahedra_QualityMeasureParameters::squareL01() const
{
	return lab_;
}

inline 
Standard_Real AutLib::GeoLib::Tetrahedra_QualityMeasureParameters::squareL12() const
{
	return lbc_;
}

inline 
Standard_Real AutLib::GeoLib::Tetrahedra_QualityMeasureParameters::squareL02() const
{
	return lac_;
}

inline 
Standard_Real AutLib::GeoLib::Tetrahedra_QualityMeasureParameters::Lrms() const
{
	return lrms_;
}

inline 
Standard_Real AutLib::GeoLib::Tetrahedra_QualityMeasureParameters::squareArea0() const
{
	return Aa_;
}

inline
Standard_Real AutLib::GeoLib::Tetrahedra_QualityMeasureParameters::squareArea1() const
{
	return Ab_;
}

inline
Standard_Real AutLib::GeoLib::Tetrahedra_QualityMeasureParameters::squareArea2() const
{
	return Ac_;
}

inline
Standard_Real AutLib::GeoLib::Tetrahedra_QualityMeasureParameters::squareArea3() const
{
	return Ad_;
}

inline 
const Geom_Pnt3d & AutLib::GeoLib::Tetrahedra_QualityMeasureParameters::t() const
{
	return t_;
}

inline 
const Geom_Pnt3d & AutLib::GeoLib::Tetrahedra_QualityMeasureParameters::u() const
{
	return u_;
}

inline 
const Geom_Pnt3d & AutLib::GeoLib::Tetrahedra_QualityMeasureParameters::v() const
{
	return v_;
}

inline
const Geom_Pnt3d& AutLib::GeoLib::Tetrahedra_QualityMeasureParameters::N0() const
{
	return Na_;
}

inline
const Geom_Pnt3d& AutLib::GeoLib::Tetrahedra_QualityMeasureParameters::N1() const
{
	return Nb_;
}

inline
const Geom_Pnt3d& AutLib::GeoLib::Tetrahedra_QualityMeasureParameters::N2() const
{
	return Nc_;
}

inline
const Geom_Pnt3d& AutLib::GeoLib::Tetrahedra_QualityMeasureParameters::N3() const
{
	return Nd_;
}