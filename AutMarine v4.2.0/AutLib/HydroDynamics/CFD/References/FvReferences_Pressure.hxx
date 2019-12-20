#pragma once
#ifndef _FvReferences_Pressure_Header
#define _FvReferences_Pressure_Header

#include <FvPrimitives_Scalar.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvReferences_Pressure
		{

		private:

			Scalar theValue_;

		public:

			FvReferences_Pressure();

			void SetValue(const Scalar theValue);

			Scalar Value() const;
		};
	}
}

#include <FvReferences_PressureI.hxx>

#endif // !_FvReferences_Pressure_Header
