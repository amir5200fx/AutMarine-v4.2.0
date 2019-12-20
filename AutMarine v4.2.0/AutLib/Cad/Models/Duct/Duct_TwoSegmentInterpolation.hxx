#pragma once
#ifndef _Duct_TwoSegmentInterpolation_Header
#define _Duct_TwoSegmentInterpolation_Header

#include <Standard_TypeDef.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Duct_TwoSegmentInterpolation
		{

		private:

			Standard_Real theMidWidth_;

			Standard_Real theMidOffset_;
			Standard_Real theInletOffset_;
			Standard_Real theOutletOffset_;

			Standard_Real theLeftTurningPosition_;
			Standard_Real theLeftTurningWidth_;

			Standard_Real theRightTurningPosition_;
			Standard_Real theRightTurningWidth_;

			Standard_Real theInletRiseWeight_;
			Standard_Real theOutletRiseWeight_;

			Standard_Real theInletWeight_;
			Standard_Real theOutletWeight_;

		public:

			Duct_TwoSegmentInterpolation();

			Standard_Real MidOffset() const;

			Standard_Real MidWidth() const;

			Standard_Real InletOffset() const;

			Standard_Real OutletOffset() const;

			Standard_Real LeftTurningPosition() const;

			Standard_Real LeftTurningWidth() const;

			Standard_Real RightTurningPosition() const;

			Standard_Real RightTurningWidth() const;

			Standard_Real InletRiseWeight() const;

			Standard_Real OutletRiseWeight() const;

			Standard_Real InletWeight() const;

			Standard_Real OutletWeight() const;

			void SetMidOffset(const Standard_Real theValue);

			void SetMidWidth(const Standard_Real theValue);

			void SetInletOffset(const Standard_Real theValue);

			void SetOutletOffset(const Standard_Real theValue);

			void SetLeftTurningPosition(const Standard_Real theValue);

			void SetLeftTurningWidth(const Standard_Real theValue);

			void SetRightTurningPosition(const Standard_Real theValue);

			void SetRightTurningWidth(const Standard_Real theValue);

			void SetInletRiseWeight(const Standard_Real theValue);

			void SetOutletRiseWeight(const Standard_Real theValue);

			void SetInletWeight(const Standard_Real theValue);

			void SetOutletWeight(const Standard_Real theValue);


		};
	}
}

#include <Duct_TwoSegmentInterpolationI.hxx>

#endif // !_Duct_TwoSegmentInterpolation_Header
