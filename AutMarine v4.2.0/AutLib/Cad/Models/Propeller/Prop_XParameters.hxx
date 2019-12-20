#pragma once
#ifndef _Prop_XParameters_Header
#define _Prop_XParameters_Header

#include <TColStd_Ary1dOfReal.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Prop_XParameters
		{

		private:

			TColStd_Ary1dOfReal theX_;

			TColStd_Ary1dOfReal thePitchAngle_;
			TColStd_Ary1dOfReal theChord_;
			TColStd_Ary1dOfReal theMaxCamber_;
			TColStd_Ary1dOfReal theMaxCamberPosition_;
			TColStd_Ary1dOfReal theSkew_;
			TColStd_Ary1dOfReal theRake_;
			TColStd_Ary1dOfReal theThickness_;
			
		public:

			Prop_XParameters();

			Prop_XParameters(const Standard_Integer theNbSegments);

			const TColStd_Ary1dOfReal& X() const;

			const TColStd_Ary1dOfReal& xPitchAngle() const;

			const TColStd_Ary1dOfReal& xChord() const;

			const TColStd_Ary1dOfReal& xMaxCamber() const;

			const TColStd_Ary1dOfReal& xMaxCamberPosition() const;

			const TColStd_Ary1dOfReal& xSkew() const;

			const TColStd_Ary1dOfReal& xRake() const;

			const TColStd_Ary1dOfReal& xThickness() const;

			Standard_Real X(const Standard_Integer theIndex) const;

			Standard_Real xPitchAngle(const Standard_Integer theIndex) const;

			Standard_Real xChord(const Standard_Integer theIndex) const;

			Standard_Real xMaxCamber(const Standard_Integer theIndex) const;

			Standard_Real xMaxCamberPosition(const Standard_Integer theIndex) const;

			Standard_Real xSkew(const Standard_Integer theIndex) const;

			Standard_Real xRake(const Standard_Integer theIndex) const;

			Standard_Real xThickness(const Standard_Integer theIndex) const;

			void SetX(const Standard_Integer theIndex, const Standard_Real theValue);

			void SetPitchAngle(const Standard_Integer theIndex, const Standard_Real theValue);

			void SetChord(const Standard_Integer theIndex, const Standard_Real theValue);

			void SetMaxCamber(const Standard_Integer theIndex, const Standard_Real theValue);

			void SetMaxCamberPosition(const Standard_Integer theIndex, const Standard_Real theValue);

			void SetSkew(const Standard_Integer theIndex, const Standard_Real theValue);

			void SetRake(const Standard_Integer theIndex, const Standard_Real theValue);

			void SetThickness(const Standard_Integer theIndex, const Standard_Real theValue);

			void AllocateMemory(const Standard_Integer theNbSegments);
		};
	}
}

#include <Prop_XParametersI.hxx>

#endif // !_Prop_XParameters_Header
