#pragma once
#ifndef _FvBC_Type_Header
#define _FvBC_Type_Header

namespace AutLib
{
	namespace FvLib
	{

		enum FvBC_Type
		{

			FvBC_Type_NONE = 0,
			FvBC_Type_INLET,
			FvBC_Type_OUTLET,
			FvBC_Type_WALL,
			FvBC_Type_SYMMETRY,
			FvBC_Type_INITIAL_VELOCITY,
			FvBC_Type_INITIAL_PRESSURE
		};
	}
}

#endif // !_FvBC_Type_Header
