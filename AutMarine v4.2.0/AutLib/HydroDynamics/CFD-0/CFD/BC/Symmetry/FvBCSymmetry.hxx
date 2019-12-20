#pragma once
#ifndef _FvBCSymmetry_Header
#define _FvBCSymmetry_Header

#include <FvBC_Boundary.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvBCSymmetry : public FvBC_Boundary
		{

		private:

		public:

			FvBCSymmetry();

			virtual ~FvBCSymmetry();


		};
	}
}

#endif // !_FvBCSymmetry_Header
