#pragma once
#ifndef _FvEntity_Element2dTools_Header
#define _FvEntity_Element2dTools_Header

namespace AutLib
{
	namespace FvLib
	{

		class FvEntity_Element2d;

		class FvEntity_Element2dTools
		{

		public:

			static void CalcGeometry(FvEntity_Element2d& theElement);
		};
	}
}

#endif // !_FvEntity_Element2dTools_Header
