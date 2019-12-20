#pragma once
#ifndef _FvReferences_Pressure_Header
#define _FvReferences_Pressure_Header

#include <Standard_TypeDef.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvReferences_Pressure
		{

		private:

			Standard_Real theValue_;

		public:

			FvReferences_Pressure();

			void SetValue(const Standard_Real theValue);

			Standard_Real Value() const;
		};
	}
}

#include <FvReferences_PressureI.hxx>

#endif // !_FvReferences_Pressure_Header
