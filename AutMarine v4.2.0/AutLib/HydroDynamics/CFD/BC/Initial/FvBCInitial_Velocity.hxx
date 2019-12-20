#pragma once
#ifndef _FvBCInitial_Velocity_Header
#define _FvBCInitial_Velocity_Header

#include <FvBC_Boundary.hxx>
#include <FvBCSpecification_VelocityMethod.hxx>

namespace AutLib
{
	namespace FvLib
	{
		
		class FvBCInitial_Velocity : public FvBC_Boundary
		{

		private:

			const FvBCSpecification_VelocityMethod& theVelocity_;

		public:

			FvBCInitial_Velocity(const FvBCSpecification_VelocityMethod& theVelocity);

			virtual ~FvBCInitial_Velocity();

			const FvBCSpecification_VelocityMethod& Velocity() const;
		};
	}
}

#include <FvBCInitial_VelocityI.hxx>

#endif // !_FvBCInitial_Velocity_Header
