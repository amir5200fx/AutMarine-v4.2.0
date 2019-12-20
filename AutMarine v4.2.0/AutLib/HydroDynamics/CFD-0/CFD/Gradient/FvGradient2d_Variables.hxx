#pragma once
#ifndef _FvGradient2d_Variables_Header
#define _FvGradient2d_Variables_Header

#include <FvGradient2d_Pressure.hxx>
#include <FvGradient2d_xVelocity.hxx>
#include <FvGradient2d_yVelocity.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvGradient2d_Variables
		{

		private:

			const FvGradient2d_Pressure& thePressure_;

			const FvGradient2d_xVelocity& thexVelocity_;
			const FvGradient2d_yVelocity& theyVelocity_;

		public:

			FvGradient2d_Variables(const FvGradient2d_Pressure& thePressure, const FvGradient2d_xVelocity& thexVelocity, const FvGradient2d_yVelocity& theyVelocity);

			const FvGradient2d_Pressure& Pressure() const;

			const FvGradient2d_xVelocity& xVelocity() const;

			const FvGradient2d_yVelocity& yVelocity() const;
		};
	}
}

#include <FvGradient2d_VariablesI.hxx>

#endif // !_FvGradient2d_Variables_Header
