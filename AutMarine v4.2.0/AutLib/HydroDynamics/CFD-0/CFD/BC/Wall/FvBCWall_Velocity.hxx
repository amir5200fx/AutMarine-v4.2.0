#pragma once
#ifndef _FvBCWall_Velocity_Header
#define _FvBCWall_Velocity_Header

#include <FvBC_Boundary.hxx>
#include <FvBCSpecification_TangentionalVelocity.hxx>

namespace AutLib
{
	namespace FvLib
	{
		
		class FvBCWall_Velocity : public FvBC_Boundary
		{

		private:

			const FvBCSpecification_TangentionalVelocity& theVelocity_;

		public:

			FvBCWall_Velocity(const FvBCSpecification_TangentionalVelocity& theVelocity);

			virtual ~FvBCWall_Velocity();

			const FvBCSpecification_TangentionalVelocity& Velocity() const;
		};
	}
}

#include <FvBCWall_VelocityI.hxx>

#endif // !_FvBCWall_Velocity_Header
