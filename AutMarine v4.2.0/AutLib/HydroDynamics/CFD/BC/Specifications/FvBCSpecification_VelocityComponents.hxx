#pragma once
#ifndef _FvBCSpecification_VelocityComponents_Header
#define _FvBCSpecification_VelocityComponents_Header

#include <FvBCSpecification_Velocity.hxx>
#include <FvBCSpecification_VelocityMethod.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvBCSpecification_VelocityComponents : public FvBCSpecification_Velocity
		{

		private:

			const FvBCSpecification_VelocityMethod& theMethod_;

		public:

			FvBCSpecification_VelocityComponents(const FvBCSpecification_VelocityMethod& theMethod);

			virtual ~FvBCSpecification_VelocityComponents();

			Vec2 Value(const Geom_Pnt2d& theCoord) const;
		};
	}
}

#include <FvBCSpecification_VelocityComponentsI.hxx>

#endif // !_FvBCSpecification_VelocityComponents_Header
