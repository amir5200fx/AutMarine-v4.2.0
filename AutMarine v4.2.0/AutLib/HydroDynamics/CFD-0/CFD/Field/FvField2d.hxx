#pragma once
#ifndef _FvField2d_Header
#define _FvField2d_Header

#include <Geom_Pnt2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		template<typename T>
		class FvField2d
		{

		private:

		public:

			virtual T Value(const Geom_Pnt2d& theCoord) const = 0;
		};
	}
}

#endif // !_FvField2d_Header
