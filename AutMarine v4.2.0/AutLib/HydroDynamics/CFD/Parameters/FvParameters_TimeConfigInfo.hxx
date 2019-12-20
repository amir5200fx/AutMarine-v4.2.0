#pragma once
#ifndef _FvParameters_TimeConfigInfo_Header
#define _FvParameters_TimeConfigInfo_Header

#include <FvPrimitives_Scalar.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvParameters_TimeConfigInfo
		{

		public:

			static Scalar Start();

			static Scalar End();

			static Scalar Step();
		};
	}
}

#endif // !_FvParameters_TimeConfigInfo_Header
