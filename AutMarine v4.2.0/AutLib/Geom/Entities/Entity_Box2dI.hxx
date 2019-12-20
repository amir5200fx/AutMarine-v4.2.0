#pragma once
#include <Global_Macros.hxx>

inline AutLib::GeoLib::Entity_Box2d::Entity_Box2d()
	: xmin_(RealFirst())
	, xmax_(RealLast())
	, ymin_(RealFirst())
	, ymax_(RealLast())
{
}

inline AutLib::GeoLib::Entity_Box2d::Entity_Box2d
(
	const Standard_Real Xmin,
	const Standard_Real Xmax,
	const Standard_Real Ymin, 
	const Standard_Real Ymax
)
	: xmin_(Xmin)
	, xmax_(Xmax)
	, ymin_(Ymin)
	, ymax_(Ymax)
{
}

inline Standard_Real AutLib::GeoLib::Entity_Box2d::Xmin() const
{
	return xmin_;
}

inline Standard_Real AutLib::GeoLib::Entity_Box2d::Xmax() const
{
	return xmax_;
}

inline Standard_Real AutLib::GeoLib::Entity_Box2d::Ymin() const
{
	return ymin_;
}

inline Standard_Real AutLib::GeoLib::Entity_Box2d::Ymax() const
{
	return ymax_;
}

inline Standard_Real& AutLib::GeoLib::Entity_Box2d::Xmin()
{
	return xmin_;
}

inline Standard_Real& AutLib::GeoLib::Entity_Box2d::Xmax()
{
	return xmax_;
}

inline Standard_Real& AutLib::GeoLib::Entity_Box2d::Ymin()
{
	return ymin_;
}

inline Standard_Real& AutLib::GeoLib::Entity_Box2d::Ymax()
{
	return ymax_;
}

inline M_GEO Entity_Box2d AutLib::GeoLib::Entity_Box2d::NwQuarter() const
{
	return Entity_Box2d
	(
		xmin_, 
		0.5*(xmin_ + xmax_),
		0.5*(ymin_ + ymax_),
		ymax_
	);
}

inline M_GEO Entity_Box2d AutLib::GeoLib::Entity_Box2d::NeQuarter() const
{
	return Entity_Box2d
	(
		0.5*(xmin_ + xmax_),
		xmax_,
		0.5*(ymin_ + ymax_),
		ymax_
	);
}

inline M_GEO Entity_Box2d AutLib::GeoLib::Entity_Box2d::SwQuarter() const
{
	return Entity_Box2d
	(
		xmin_,
		0.5*(xmin_ + xmax_),
		ymin_,
		0.5*(ymin_ + ymax_)
	);
}

inline M_GEO Entity_Box2d AutLib::GeoLib::Entity_Box2d::SeQuarter() const
{
	return Entity_Box2d
	(
		0.5*(xmin_ + xmax_),
		xmax_,
		ymin_,
		0.5*(ymin_ + ymax_)
	);
}

inline
M_GEO Entity_Box2d AutLib::GeoLib::Entity_Box2d::LeftHalf() const
{
	Entity_Box2d newBox
	(
		xmin_,
		0.5*(xmin_ + xmax_),
		ymin_,
		ymax_
	);

	MOVE(newBox);
}

inline
M_GEO Entity_Box2d AutLib::GeoLib::Entity_Box2d::RightHalf() const
{
	Entity_Box2d newBox
	(
		0.5*(xmin_ + xmax_),
		xmax_,
		ymin_,
		ymax_
	);

	MOVE(newBox);
}

inline
M_GEO Entity_Box2d AutLib::GeoLib::Entity_Box2d::UpHalf() const
{
	Entity_Box2d newBox
	(
		xmin_,
		xmax_,
		0.5*(ymin_ + ymax_),
		ymin_
	);

	MOVE(newBox);
}

inline
M_GEO Entity_Box2d AutLib::GeoLib::Entity_Box2d::DownHalf() const
{
	Entity_Box2d newBox
	(
		xmin_,
		xmax_,
		ymin_,
		0.5*(ymin_ + ymax_)
	);

	MOVE(newBox);
}

inline M_GEO Entity_Box2d AutLib::GeoLib::Entity_Box2d::OffsetBox(const Standard_Real Tolerance) const
{
	return Entity_Box2d
	(
		xmin_ - Tolerance,
		xmax_ + Tolerance,
		ymin_ - Tolerance,
		ymax_ + Tolerance
	);
}

inline Geom_Pnt2d AutLib::GeoLib::Entity_Box2d::CalcCentre() const
{
	return Geom_Pnt2d
	(
		0.5*(xmin_ + xmax_),
		0.5*(ymin_ + ymax_)
	);
}

inline
Geom_Pnt2d AutLib::GeoLib::Entity_Box2d::GetNwPoint() const
{
	Geom_Pnt2d NwPoint(xmin_, ymax_);

	MOVE(NwPoint);
}

inline
Geom_Pnt2d AutLib::GeoLib::Entity_Box2d::GetNePoint() const
{
	Geom_Pnt2d NePoint(xmax_, ymax_);

	MOVE(NePoint);
}

inline
Geom_Pnt2d AutLib::GeoLib::Entity_Box2d::GetSwPoint() const
{
	Geom_Pnt2d SwPoint(xmin_, ymin_);

	MOVE(SwPoint);
}

inline
Geom_Pnt2d AutLib::GeoLib::Entity_Box2d::GetSePoint() const
{
	Geom_Pnt2d SePoint(xmax_, ymin_);

	MOVE(SePoint);
}

inline
Standard_Real AutLib::GeoLib::Entity_Box2d::Diameter() const
{
	return sqrt(DiameterSQ());
}

inline
Standard_Real AutLib::GeoLib::Entity_Box2d::DiameterSQ() const
{
	Standard_Real dx = xmax_ - xmin_;
	Standard_Real dy = ymax_ - ymin_;

	return dx*dx + dy*dy;
}

inline 
void AutLib::GeoLib::Entity_Box2d::Exapnd(const Standard_Real theValue)
{
	xmin_ -= theValue;
	xmax_ += theValue;
	ymin_ -= theValue;
	ymax_ += theValue;
}

inline 
void AutLib::GeoLib::Entity_Box2d::Get
(
	Standard_Real & theXmin,
	Standard_Real & theXmax, 
	Standard_Real & theYmin, 
	Standard_Real & theYmax
) const
{
	theXmin = xmin_;
	theXmax = xmax_;
	theYmin = ymin_;
	theYmax = ymax_;
}