#pragma once

#include <Geometry_Tools.hxx>

inline
const M_GEO Entity_TriangleIndex & AutLib::GeoLib::DelTri2d::Vertex(const Standard_Integer Index) const
{
	Debug_Bad_Index_Array1(Index, theV_);

	return theV_[Index];
}

inline 
const M_GEO Entity_TriangleIndex & AutLib::GeoLib::DelTri2d::Neighbor(const Standard_Integer Index) const
{
	Debug_Bad_Index_Array1(Index, theE_);

	return theE_[Index];
}

inline 
const M_AUT TColEntity_Ary1dOfTriangleIndex & AutLib::GeoLib::DelTri2d::Vertices() const
{
	return theV_;
}

inline 
const M_AUT TColEntity_Ary1dOfTriangleIndex & AutLib::GeoLib::DelTri2d::Neighbors() const
{
	return theE_;
}

inline 
Standard_Integer AutLib::GeoLib::DelTri2d::NbElements() const
{
	return theNbTris_;
}

inline 
Standard_Integer AutLib::GeoLib::DelTri2d::Edge
(
	const Standard_Integer L,
	const Standard_Integer K
) const
{
	forThose(Index, 0, 2)
		if (theE_[Index_Of(L)].Value(Index) EQUAL K) return Index;

	return -1;
}

inline 
Standard_Integer AutLib::GeoLib::DelTri2d::TriLoc(const Geom_Pnt2d & Pt) const
{
	return TriLoc(Pt, theNbTris_);
}

inline 
Standard_Integer AutLib::GeoLib::DelTri2d::TriLoc
(
	const Geom_Pnt2d & Pt,
	const Standard_Integer i
) const
{
	if (i == 0) return 0;

	Standard_Integer v1 = theV_[i - 1].V0() - 1;
	Standard_Integer v2 = theV_[i - 1].V1() - 1;
	Standard_Integer v3 = theV_[i - 1].V2() - 1;

	if (IsRightSide(Pt, thePts_[v1], thePts_[v2]))
		return TriLoc(Pt, theE_[i - 1].V0());
	else if (IsRightSide(Pt, thePts_[v2], thePts_[v3]))
		return TriLoc(Pt, theE_[i - 1].V1());
	else if (IsRightSide(Pt, thePts_[v3], thePts_[v1]))
		return TriLoc(Pt, theE_[i - 1].V2());
	else
		return i;
}

inline 
Standard_Boolean AutLib::GeoLib::DelTri2d::Swap
(
	const Geom_Pnt2d & Pt,
	const Geom_Pnt2d & P1, 
	const Geom_Pnt2d & P2, 
	const Geom_Pnt2d & P3
) const
{
	Standard_Real x13 = P1.X() - P3.X();
	Standard_Real y13 = P1.Y() - P3.Y();
	Standard_Real x23 = P2.X() - P3.X();
	Standard_Real y23 = P2.Y() - P3.Y();
	Standard_Real x1p = P1.X() - Pt.X();
	Standard_Real y1p = P1.Y() - Pt.Y();
	Standard_Real x2p = P2.X() - Pt.X();
	Standard_Real y2p = P2.Y() - Pt.Y();

	Standard_Real cosa = x13*x23 + y13*y23;
	Standard_Real cosb = x2p*x1p + y1p*y2p;

	if ((cosa >= 0) && (cosb >= 0))
		return Standard_False;
	else if ((cosa < 0) && (cosb < 0))
		return Standard_True;
	else
	{
		Standard_Real sina = x13*y23 - x23*y13;
		Standard_Real sinb = x2p*y1p - x1p*y2p;

		if ((sina*cosb + sinb*cosa) < 0)
			return Standard_True;
		else
			return Standard_False;
	}
}

inline
Standard_Boolean AutLib::GeoLib::DelTri2d::IsRightSide
(
	const Geom_Pnt2d & Pt, 
	const Geom_Pnt2d & P1, 
	const Geom_Pnt2d & P2
) const
{
	return Geometry_Tools::IsPointRightEdge(Pt, P1, P2);
}