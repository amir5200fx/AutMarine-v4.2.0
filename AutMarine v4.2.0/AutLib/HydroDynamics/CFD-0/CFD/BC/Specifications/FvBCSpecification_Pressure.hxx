#pragma once
#ifndef _FvBCSpecification_Pressure_Header
#define _FvBCSpecification_Pressure_Header

#include <Standard_TypeDef.hxx>
#include <FvField2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvBCSpecification_Pressure
		{

		private:

			const FvField2d<Standard_Real>& theField_;

		public:

			FvBCSpecification_Pressure(const FvField2d<Standard_Real>& theField);

			Standard_Real Value(const Geom_Pnt2d& theCoord) const;
		};
	}
}

#include <FvBCSpecification_PressureI.hxx>

#endif // !_FvBCSpecification_Pressure_Header
