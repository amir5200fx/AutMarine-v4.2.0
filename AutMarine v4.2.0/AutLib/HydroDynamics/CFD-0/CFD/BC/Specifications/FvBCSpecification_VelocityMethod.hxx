#pragma once
#ifndef _FvBCSpecification_VelocityMethod_Header
#define _FvBCSpecification_VelocityMethod_Header

#include <Geom_Pnt2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvBCSpecification_VelocityMethod
		{

		private:


		public:

			virtual Geom_Pnt2d Value(const Geom_Pnt2d& theCoord) const = 0;
		};
	}
}

#endif // !_FvBCSpecification_VelocityMethod_Header
