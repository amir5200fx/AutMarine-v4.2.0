#pragma once
#ifndef _FvParameters_ConstTimeStep_Header
#define _FvParameters_ConstTimeStep_Header

#include <FvParameters_TimeConfig.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvParameters_ConstTimeStep : public FvParameters_TimeConfig
		{

		private:

			Scalar theStep_;

		public:

			FvParameters_ConstTimeStep();

			virtual ~FvParameters_ConstTimeStep();

			Scalar Step() const;

			void SetStep(const Scalar theValue);
		};
	}
}

#include <FvParameters_ConstTimeStepI.hxx>

#endif // !_FvParameters_ConstTimeStep_Header
