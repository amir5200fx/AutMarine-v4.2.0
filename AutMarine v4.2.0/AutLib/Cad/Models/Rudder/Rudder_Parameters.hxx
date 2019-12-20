#pragma once
#ifndef _Rudder_Parameters_Header
#define _Rudder_Parameters_Header

#include <Standard_TypeDef.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Rudder_Parameters
		{

		private:

			Standard_Real theChord_;
			Standard_Real theSpan_;

			Standard_Real theThickness_;

			Standard_Real theShaftLength_;
			Standard_Real theShaftDiameter_;
			Standard_Real theShaftPosition_;

		public:

			Rudder_Parameters();

			Standard_Real Chord() const;

			Standard_Real Span() const;

			Standard_Real Thickness() const;

			Standard_Real ShaftLength() const;

			Standard_Real ShaftDiameter() const;

			Standard_Real ShaftPosition() const;

			void SetChord(const Standard_Real theValue);

			void SetSpan(const Standard_Real theValue);

			void SetThickness(const Standard_Real theValue);

			void SetShaftLength(const Standard_Real theValue);

			void SetShaftDiameter(const Standard_Real theValue);

			void SetShaftPosition(const Standard_Real theValue);
		};
	}
}

#include <Rudder_ParametersI.hxx>

#endif // !_Rudder_Parameters_Header
