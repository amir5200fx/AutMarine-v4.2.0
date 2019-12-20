#pragma once
#ifndef _FvBCSpecification_VelocityMethodFieldFunction_Header
#define _FvBCSpecification_VelocityMethodFieldFunction_Header

#include <FvBCSpecification_VelocityMethod.hxx>
#include <FvField2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvBCSpecification_VelocityMethodFieldFunction : public FvBCSpecification_VelocityMethod
		{

		private:

			const FvField2d<Geom_Pnt2d>& theField_;

		public:

			FvBCSpecification_VelocityMethodFieldFunction(const FvField2d<Geom_Pnt2d>& theField);

			virtual Geom_Pnt2d Value(const Geom_Pnt2d& theCoord) const;
		};
	}
}

#include <FvBCSpecification_VelocityMethodFieldFunctionI.hxx>

#endif // !_FvBCSpecification_VelocityMethodFieldFunction_Header
