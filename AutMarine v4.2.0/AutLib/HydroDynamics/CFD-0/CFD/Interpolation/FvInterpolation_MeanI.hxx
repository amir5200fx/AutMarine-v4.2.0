#pragma once
#include <Global_Debug.hxx>

inline
Standard_Real AutLib::FvLib::FvInterpolation_Mean::Interpolate
(
	const FvEntity_Face2d & theFace,
	const Standard_Boolean theBoundary
) const
{
	if (theFace.Pair())
	{
		Debug_Null_Pointer(theFace.Pair()->Element());
		Debug_Null_Pointer(theFace.Element());

		Get_Const_Object(Neighbor) = *theFace.Pair()->Element();
		Get_Const_Object(Element) = *theFace.Element();

		return MEAN(V_GetCmp((Vector*)&thePhi_, Neighbor.Index()), V_GetCmp((Vector*)&thePhi_, Element.Index()));
	}
	else
	{
		if (theBoundary)
			return V_GetCmp((Vector*)&thePhif_, theFace.Index());
		else
		{
			Debug_Null_Pointer(theFace.Pair()->Element());

			Get_Const_Object(Element) = *theFace.Element();

			return V_GetCmp((Vector*)&thePhi_, Element.Index());
		}
	}
}

inline 
Standard_Real AutLib::FvLib::FvInterpolation_Mean::Interpolate
(
	const FvEntity_Face2d & theFace,
	const FvVariables_Faces2d & thePhif, 
	const FvVariables_Elements2d & thePhi,
	const Standard_Boolean theBoundary
)
{
	if (theFace.Pair())
	{
		Debug_Null_Pointer(theFace.Pair()->Element());
		Debug_Null_Pointer(theFace.Element());

		Get_Const_Object(Neighbor) = *theFace.Pair()->Element();
		Get_Const_Object(Element) = *theFace.Element();

		return MEAN(V_GetCmp((Vector*)&thePhi, Neighbor.Index()), V_GetCmp((Vector*)&thePhi, Element.Index()));
	}
	else
	{
		if (theBoundary)
			return V_GetCmp((Vector*)&thePhif, theFace.Index());
		else
		{
			Debug_Null_Pointer(theFace.Pair()->Element());

			Get_Const_Object(Element) = *theFace.Element();

			return V_GetCmp((Vector*)&thePhi, Element.Index());
		}
	}
}

inline 
Geom_Pnt2d AutLib::FvLib::FvInterpolation_Mean::Interpolate
(
	const FvEntity_Face2d & theFace, 
	const TColGeom_Ary1dOfPnt2d & thePhi
)
{
	if (theFace.Pair())
	{
		Debug_Null_Pointer(theFace.Pair()->Element());
		Debug_Null_Pointer(theFace.Element());

		Get_Const_Object(Neighbor) = *theFace.Pair()->Element();
		Get_Const_Object(Element) = *theFace.Element();

		return MEAN(thePhi.Value(Neighbor.Index()), thePhi.Value(Element.Index()));
	}
	else
	{
		Debug_Null_Pointer(theFace.Pair()->Element());

		Get_Const_Object(Element) = *theFace.Element();

		return thePhi.Value(Element.Index());
	}
}