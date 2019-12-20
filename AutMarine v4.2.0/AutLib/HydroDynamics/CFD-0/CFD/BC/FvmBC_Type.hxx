#pragma once
#ifndef _FvmBC_Type_Header
#define _FvmBC_Type_Header

namespace AutLib
{
	namespace FvmLib
	{

		enum FvmBC_Type
		{

			FvmBC_Type_NONE = 0,
			FvmBC_Type_INLET,
			FvmBC_Type_OUTLET,
			FvmBC_Type_WALL,
			FvmBC_Type_SYMMETRY
		};
	}
}

#endif // !_FvmBC_Type_Header
