#pragma once
#ifndef _Model2d_Naca4DigitParameters_Header
#define _Model2d_Naca4DigitParameters_Header

#include <Standard_TypeDef.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Model2d_Naca4DigitParameters
		{

		private:

			Standard_Real theChord_;
			Standard_Real theMaxCamber_;
			Standard_Real theMaxCamberPosition_;
			Standard_Real theMaxThickness_;

		public:

			Model2d_Naca4DigitParameters();

			//! Throw an exception if a parameter is not inside the default values
			void Init(const Standard_Real Chord, const Standard_Real MaxCamber, const Standard_Real MaxCamberPosition, const Standard_Real MaxThickness);

			//! Throw an exception if a parameter is not inside the default values
			void SetChord(const Standard_Real Chord);

			//! Throw an exception if a parameter is not inside the default values
			void SetMaxCamber(const Standard_Real MaxCamber);

			//! Throw an exception if a parameter is not inside the default values
			void SetMaxCamberPosition(const Standard_Real MaxCamberPosition);

			//! Throw an exception if a parameter is not inside the default values
			void SetMaxThickness(const Standard_Real MaxThickness);

			Standard_Real Chord() const;

			Standard_Real MaxCamber() const;

			Standard_Real MaxCamberPosition() const;

			Standard_Real MaxThickness() const;
		};
	}
}

#include <Model2d_Naca4DigitParametersI.hxx>

#endif // !_Model2d_Naca4DigitParameters_Header
