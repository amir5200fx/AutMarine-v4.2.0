#pragma once
#ifndef _FvParameters_TimeConfigInfo_Header
#define _FvParameters_TimeConfigInfo_Header

#include <Standard_TypeDef.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvParameters_TimeConfigInfo
		{

		public:

			static Standard_Real Start();

			static Standard_Real End();

			static Standard_Real Step();
		};
	}
}

#endif // !_FvParameters_TimeConfigInfo_Header
