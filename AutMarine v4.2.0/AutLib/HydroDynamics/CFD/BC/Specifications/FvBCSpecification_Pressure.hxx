#pragma once
#ifndef _FvBCSpecification_Pressure_Header
#define _FvBCSpecification_Pressure_Header

#include <FvField2d_Scalar.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvBCSpecification_Pressure
		{

		private:

			const FvField2d_Scalar& theField_;

		public:

			FvBCSpecification_Pressure(const FvField2d_Scalar& theField);

			Scalar Value(const Geom_Pnt2d& theCoord) const;
		};
	}
}

#include <FvBCSpecification_PressureI.hxx>

#endif // !_FvBCSpecification_Pressure_Header
