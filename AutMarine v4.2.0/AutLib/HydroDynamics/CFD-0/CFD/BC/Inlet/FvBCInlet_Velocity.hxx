#pragma once
#ifndef _FvBCInlet_Velocity_Header
#define _FvBCInlet_Velocity_Header

#include <FvBC_Boundary.hxx>
#include <FvBCSpecification_Velocity.hxx>

namespace AutLib
{
	namespace FvLib
	{
		
		class FvBCInlet_Velocity : public FvBC_Boundary
		{

		private:

			const FvBCSpecification_Velocity& theVelocity_;

		public:

			FvBCInlet_Velocity(const FvBCSpecification_Velocity& theVelocity);

			virtual ~FvBCInlet_Velocity();

			const FvBCSpecification_Velocity& Velocity() const;
		};
	}
}

#include <FvBCInlet_VelocityI.hxx>

#endif // !_FvBCInlet_Velocity_Header
