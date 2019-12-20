#pragma once
#ifndef _Compound_ShipRudderSystemParameters_Header
#define _Compound_ShipRudderSystemParameters_Header

#include <Standard_TypeDef.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Compound_ShipRudderSystemParameters
		{

		private:

			Standard_Real theX_;
			Standard_Real theY_;
			Standard_Real theZ_;

			Standard_Real theShaftInclination_;

		public:

			Compound_ShipRudderSystemParameters();

			Standard_Real X() const;

			Standard_Real Y() const;

			Standard_Real Z() const;

			Standard_Real ShaftInclination() const;

			void SetX(const Standard_Real theX);

			void SetY(const Standard_Real theY);

			void SetZ(const Standard_Real theZ);

			void SetShaftInclination(const Standard_Real theInclination);
		};
	}
}

#include <Compound_ShipRudderSystemParametersI.hxx>

#endif // !_Compound_ShipRudderSystemParameters_Header
