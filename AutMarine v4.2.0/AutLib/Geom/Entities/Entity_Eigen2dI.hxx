#pragma once
#include <Global_Debug.hxx>

inline const Geom_Pnt2d& AutLib::GeoLib::Entity_Eigen2d::E1() const
{
	Debug_If_Condition(NOT IsDone_);
	return theE1_;
}

inline const Geom_Pnt2d& AutLib::GeoLib::Entity_Eigen2d::E2() const
{
	Debug_If_Condition(NOT IsDone_);
	return theE2_;
}

inline Standard_Real AutLib::GeoLib::Entity_Eigen2d::H1() const
{
	Debug_If_Condition(NOT IsDone_);
	return theH1_;
}

inline Standard_Real AutLib::GeoLib::Entity_Eigen2d::H2() const
{
	Debug_If_Condition(NOT IsDone_);
	return theH2_;
}

inline Standard_Real AutLib::GeoLib::Entity_Eigen2d::Lamda1() const
{
	Debug_If_Condition(NOT IsDone_);
	return theLamda1_;
}

inline Standard_Real AutLib::GeoLib::Entity_Eigen2d::Lamda2() const
{
	Debug_If_Condition(NOT IsDone_);
	return theLamda2_;
}