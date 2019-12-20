#pragma once
#ifndef _Duct_ConstParameters_Header
#define _Duct_ConstParameters_Header

#include <Standard_TypeDef.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Duct_ConstParameters
		{

		public:

			static Standard_Integer LevelOfSmoothing();

			static Standard_Real SmoothWeight();

			static Standard_Real MaxLength();

			static Standard_Real MinLength();

			static Standard_Real MaxBreadth();

			static Standard_Real MinBreadth();

			static Standard_Real MaxDepth();

			static Standard_Real MinDepth();

			static Standard_Integer MaxNbSections();

			static Standard_Integer MinNbSections();


		};
	}
}

#define Set_DuctParameterValue(X, MinValue, MaxValue, Parameter) \
    Parameter = X;                                               \
    if (Parameter < MinValue) Parameter = MinValue;              \
    if (Parameter > MaxValue) Parameter = MaxValue;

#endif // !_Duct_ConstParameters_Header
