#pragma once
#ifndef _FvBCSpecification_VelocityMagnitudeDirection_Header
#define _FvBCSpecification_VelocityMagnitudeDirection_Header

#include <FvBCSpecification_Velocity.hxx>
#include <FvBCSpecification_FlowDirection.hxx>
#include <FvField2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvBCSpecification_VelocityMagnitudeDirection : public FvBCSpecification_Velocity
		{

		private:

			const FvField2d<Standard_Real>& theField_;

			const FvBCSpecification_FlowDirection& theDirection_;

		public:

			FvBCSpecification_VelocityMagnitudeDirection(const FvField2d<Standard_Real>& theField, const FvBCSpecification_FlowDirection& theDirection);

			virtual ~FvBCSpecification_VelocityMagnitudeDirection();

			const FvBCSpecification_FlowDirection& Direction() const;

			Standard_Real Magnitude(const Geom_Pnt2d& theCoord) const;
		};
	}
}

#include <FvBCSpecification_VelocityMagnitudeDirectionI.hxx>

#endif // !_FvBCSpecification_VelocityMagnitudeDirection_Header
