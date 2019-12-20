#pragma once
inline
AutLib::GeoLib::Entity_Box3d::Entity_Box3d()
	: theXmin_(RealFirst())
	, theYmin_(RealFirst())
	, theZmin_(RealFirst())
	, theXmax_(RealLast())
	, theYmax_(RealLast())
	, theZmax_(RealLast())
{
}

inline
AutLib::GeoLib::Entity_Box3d::Entity_Box3d
(
	const Standard_Real Xmin,
	const Standard_Real Xmax,
	const Standard_Real Ymin,
	const Standard_Real Ymax,
	const Standard_Real Zmin,
	const Standard_Real Zmax
)
	: theXmin_(Xmin)
	, theXmax_(Xmax)
	, theYmin_(Ymin)
	, theYmax_(Ymax)
	, theZmin_(Zmin)
	, theZmax_(Zmax)
{
}

inline 
AutLib::GeoLib::Entity_Box3d::Entity_Box3d
(
	const Geom_Pnt3d & MinCorner,
	const Geom_Pnt3d & MaxCorner
)
	: theXmin_(MinCorner.X())
	, theYmin_(MinCorner.Y())
	, theZmin_(MinCorner.Z())
	, theXmax_(MaxCorner.X())
	, theYmax_(MaxCorner.Y())
	, theZmax_(MaxCorner.Z())
{
}

inline
Standard_Real AutLib::GeoLib::Entity_Box3d::Xmin() const
{
	return theXmin_;
}

inline
Standard_Real AutLib::GeoLib::Entity_Box3d::Xmax() const
{
	return theXmax_;
}

inline
Standard_Real AutLib::GeoLib::Entity_Box3d::Ymin() const
{
	return theYmin_;
}

inline
Standard_Real AutLib::GeoLib::Entity_Box3d::Ymax() const
{
	return theYmax_;
}

inline
Standard_Real AutLib::GeoLib::Entity_Box3d::Zmin() const
{
	return theZmin_;
}

inline
Standard_Real AutLib::GeoLib::Entity_Box3d::Zmax() const
{
	return theZmax_;
}

inline
Standard_Real & AutLib::GeoLib::Entity_Box3d::Xmin()
{
	return theXmin_;
}

inline
Standard_Real & AutLib::GeoLib::Entity_Box3d::Xmax()
{
	return theXmax_;
}

inline
Standard_Real & AutLib::GeoLib::Entity_Box3d::Ymin()
{
	return theYmin_;
}

inline
Standard_Real & AutLib::GeoLib::Entity_Box3d::Ymax()
{
	return theYmax_;
}

inline
Standard_Real & AutLib::GeoLib::Entity_Box3d::Zmin()
{
	return theZmin_;
}

inline
Standard_Real & AutLib::GeoLib::Entity_Box3d::Zmax()
{
	return theZmax_;
}

inline
M_GEO Entity_Box3d AutLib::GeoLib::Entity_Box3d::Fwd_NwOctant() const
{
	return Entity_Box3d
	(
		theXmin_,
		MEAN(theXmin_, theXmax_),
		MEAN(theYmin_, theYmax_),
		theYmax_,
		MEAN(theZmin_, theZmax_),
		theZmax_
	);
}

inline
M_GEO Entity_Box3d AutLib::GeoLib::Entity_Box3d::Fwd_NeOctant() const
{
	return Entity_Box3d
	(
		MEAN(theXmin_, theXmax_),
		theXmax_,
		MEAN(theYmin_, theYmax_),
		theYmax_,
		MEAN(theZmin_, theZmax_),
		theZmax_
	);
}

inline
M_GEO Entity_Box3d AutLib::GeoLib::Entity_Box3d::Fwd_SwOctant() const
{
	return Entity_Box3d
	(
		theXmin_,
		MEAN(theXmin_, theXmax_),
		theYmin_,
		MEAN(theYmin_, theYmax_),
		MEAN(theZmin_, theZmax_),
		theZmax_
	);
}

inline
M_GEO Entity_Box3d AutLib::GeoLib::Entity_Box3d::Fwd_SeOctant() const
{
	return Entity_Box3d
	(
		MEAN(theXmin_, theXmax_),
		theXmax_,
		theYmin_,
		MEAN(theYmin_, theYmax_),
		MEAN(theZmin_, theZmax_),
		theZmax_
	);
}

inline
M_GEO Entity_Box3d AutLib::GeoLib::Entity_Box3d::Bwd_NwOctant() const
{
	return Entity_Box3d
	(
		theXmin_,
		MEAN(theXmin_, theXmax_),
		MEAN(theYmin_, theYmax_),
		theYmax_,
		theZmin_,
		MEAN(theZmin_, theZmax_)
	);
}

inline
M_GEO Entity_Box3d AutLib::GeoLib::Entity_Box3d::Bwd_NeOctant() const
{
	return Entity_Box3d
	(
		MEAN(theXmin_, theXmax_),
		theXmax_,
		MEAN(theYmin_, theYmax_),
		theYmax_,
		theZmin_,
		MEAN(theZmin_, theZmax_)
	);
}

inline
M_GEO Entity_Box3d AutLib::GeoLib::Entity_Box3d::Bwd_SwOctant() const
{
	return Entity_Box3d
	(
		theXmin_,
		MEAN(theXmin_, theXmax_),
		theYmin_,
		MEAN(theYmin_, theYmax_),
		theZmin_,
		MEAN(theZmin_, theZmax_)
	);
}

inline
M_GEO Entity_Box3d AutLib::GeoLib::Entity_Box3d::Bwd_SeOctant() const
{
	return Entity_Box3d
	(
		MEAN(theXmin_, theXmax_),
		theXmax_,
		theYmin_,
		MEAN(theYmin_, theYmax_),
		theZmin_,
		MEAN(theZmin_, theZmax_)
	);
}

inline
M_GEO Entity_Box3d AutLib::GeoLib::Entity_Box3d::LeftHalf() const
{
	return Entity_Box3d(theXmin_, MEAN(theXmin_, theXmax_), theYmin_, theYmax_, theZmin_, theZmax_);
}

inline
M_GEO Entity_Box3d AutLib::GeoLib::Entity_Box3d::RightHalf() const
{
	return Entity_Box3d(MEAN(theXmin_, theXmax_), theXmax_, theYmin_, theYmax_, theZmin_, theZmax_);
}

inline
M_GEO Entity_Box3d AutLib::GeoLib::Entity_Box3d::UpHalf() const
{
	return Entity_Box3d(theXmin_, theXmax_, MEAN(theYmin_, theYmax_), theYmax_, theZmin_, theZmax_);
}

inline
M_GEO Entity_Box3d AutLib::GeoLib::Entity_Box3d::DownHalf() const
{
	return Entity_Box3d(theXmin_, theXmax_, theYmin_, MEAN(theYmin_, theYmax_), theZmin_, theZmax_);
}

inline
M_GEO Entity_Box3d AutLib::GeoLib::Entity_Box3d::FwdHalf() const
{
	return Entity_Box3d(theXmin_, theXmax_, theYmin_, theYmax_, MEAN(theZmin_, theZmax_), theZmax_);
}

inline
M_GEO Entity_Box3d AutLib::GeoLib::Entity_Box3d::BwdHalf() const
{
	return Entity_Box3d(theXmin_, theXmax_, theYmin_, theYmax_, theZmin_, MEAN(theZmin_, theZmax_));
}

inline
M_GEO Entity_Box3d AutLib::GeoLib::Entity_Box3d::OffsetBox(const Standard_Real Tolerance) const
{
	return Entity_Box3d(theXmin_ - Tolerance, theXmax_ + Tolerance, theYmin_ - Tolerance, theYmax_ + Tolerance, theZmin_ - Tolerance, theZmax_ + Tolerance);
}

inline
void AutLib::GeoLib::Entity_Box3d::InitUnitBox()
{
	theXmin_ = theYmin_ = theZmin_ = 0;
	theXmax_ = theYmax_ = theZmax_ = 1;
}

inline
Geom_Pnt3d AutLib::GeoLib::Entity_Box3d::CalcCentre() const
{
	return Geom_Pnt3d(MEAN(theXmin_, theXmax_), MEAN(theYmin_, theYmax_), MEAN(theZmin_, theZmax_));
}

inline
Geom_Pnt3d AutLib::GeoLib::Entity_Box3d::Fwd_NwCorner() const
{
	return Geom_Pnt3d(theXmin_, theYmax_, theZmax_);
}

inline
Geom_Pnt3d AutLib::GeoLib::Entity_Box3d::Fwd_NeCorner() const
{
	return Geom_Pnt3d(theXmax_, theYmax_, theZmax_);
}

inline
Geom_Pnt3d AutLib::GeoLib::Entity_Box3d::Fwd_SwCorner() const
{
	return Geom_Pnt3d(theXmin_, theYmin_, theZmax_);
}

inline
Geom_Pnt3d AutLib::GeoLib::Entity_Box3d::Fwd_SeCorner() const
{
	return Geom_Pnt3d(theXmax_, theYmin_, theZmax_);
}

inline
Geom_Pnt3d AutLib::GeoLib::Entity_Box3d::Bwd_NwCorner() const
{
	return Geom_Pnt3d(theXmin_, theYmax_, theZmin_);
}

inline
Geom_Pnt3d AutLib::GeoLib::Entity_Box3d::Bwd_NeCorner() const
{
	return Geom_Pnt3d(theXmax_, theYmax_, theZmin_);
}

inline
Geom_Pnt3d AutLib::GeoLib::Entity_Box3d::Bwd_SwCorner() const
{
	return Geom_Pnt3d(theXmin_, theYmin_, theZmin_);
}

inline
Geom_Pnt3d AutLib::GeoLib::Entity_Box3d::Bwd_SeCorner() const
{
	return Geom_Pnt3d(theXmax_, theYmin_, theZmin_);
}

inline
Standard_Real AutLib::GeoLib::Entity_Box3d::Diameter() const
{
	return sqrt(DiameterSQ());
}

inline
Standard_Real AutLib::GeoLib::Entity_Box3d::DiameterSQ() const
{
	Standard_Real Dx = theXmax_ - theXmin_;
	Standard_Real Dy = theYmax_ - theYmin_;
	Standard_Real Dz = theZmax_ - theZmin_;

	return Dx*Dx + Dy*Dy + Dz*Dz;
}

inline 
void AutLib::GeoLib::Entity_Box3d::Expand(const Standard_Real Offset)
{
	theXmin_ -= Offset;
	theYmin_ -= Offset;
	theZmin_ -= Offset;

	theXmax_ += Offset;
	theYmax_ += Offset;
	theZmax_ += Offset;
}