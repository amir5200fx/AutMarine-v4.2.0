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

			Standard_Real theStep_;

		public:

			FvParameters_ConstTimeStep();

			virtual ~FvParameters_ConstTimeStep();

			Standard_Real Step() const;

			void SetStep(const Standard_Real theValue);
		};
	}
}

#include <FvParameters_ConstTimeStepI.hxx>

#endif // !_FvParameters_ConstTimeStep_Header
