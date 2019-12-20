#pragma once
#ifndef _FvBCSpecification_TangentionalVelocityVector_Header
#define _FvBCSpecification_TangentionalVelocityVector_Header

#include <FvBCSpecification_TangentionalVelocity.hxx>
#include <FvBCSpecification_VelocityMethod.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvBCSpecification_TangentionalVelocityVector : public FvBCSpecification_TangentionalVelocity
		{

		private:

			const FvBCSpecification_VelocityMethod& theMethod_;

		public:

			FvBCSpecification_TangentionalVelocityVector(const FvBCSpecification_VelocityMethod& theMethod);

			virtual ~FvBCSpecification_TangentionalVelocityVector();

			const FvBCSpecification_VelocityMethod& Method() const;

			Geom_Pnt2d Value(const Geom_Pnt2d& theCoord) const;
		};
	}
}

#include <FvBCSpecification_TangentionalVelocityVectorI.hxx>

#endif // !_FvBCSpecification_TangentionalVelocityVector_Header
