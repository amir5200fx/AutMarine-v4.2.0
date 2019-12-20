#pragma once
#ifndef _FvParameters_TimeConfig_Header
#define _FvParameters_TimeConfig_Header

#include <FvPrimitives_Scalar.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvParameters_TimeConfig
		{

		private:

			Scalar theStart_;
			Scalar theEnd_;
			

		public:

			virtual ~FvParameters_TimeConfig();

			Scalar Start() const;

			Scalar End() const;

			void SetStart(const Scalar theValue);

			void SetEnd(const Scalar theValue);

			virtual Scalar Step() const = 0;

		protected:

			FvParameters_TimeConfig();
		};
	}
}

#include <FvParameters_TimeConfigI.hxx>

#endif // !_FvParameters_TimeConfig_Header
