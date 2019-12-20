#pragma once
#ifndef _Compound_BoundedParameter_Header
#define _Compound_BoundedParameter_Header

#include <Standard_Real.hxx>
#include <Standard_OStream.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Compound_BoundedParameter
		{

		private:

			Standard_Real theMin_;
			Standard_Real theMax_;

		public:

			Compound_BoundedParameter();

			Compound_BoundedParameter(const Standard_Real theMin, const Standard_Real theMax);

			void Init(const Standard_Real theMin, const Standard_Real theMax);

			void SetMin(const Standard_Real theMin);

			void SetMax(const Standard_Real theMax);

			Standard_Real Min() const;

			Standard_Real Max() const;

			void Print(Standard_OStream& Ostream) const;
		};
	}
}

#include <Compound_BoundedParameterI.hxx>

#endif // !_Compound_BoundedParameter_Header
