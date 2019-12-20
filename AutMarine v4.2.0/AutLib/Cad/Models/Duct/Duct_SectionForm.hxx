#pragma once
#ifndef _Duct_SectionForm_Header
#define _Duct_SectionForm_Header

#include <Standard_TypeDef.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Duct_SectionForm
		{

		private:

			Standard_Real theSideSlope_;
			Standard_Real theUpperTightness_;
			Standard_Real theLowerTightness_;
			Standard_Real theWidth_;

		public:

			Duct_SectionForm();

			Standard_Real SideSlope() const;

			Standard_Real UpperTightness() const;

			Standard_Real LowerTightness() const;

			Standard_Real Width() const;

			void SetSideSlope(const Standard_Real theSideSlope);

			void SetUpperTightness(const Standard_Real theUpperTightness);

			void SetLowerTightness(const Standard_Real theLowerTightness);

			void SetWidth(const Standard_Real theHeight);
		};
	}
}

#include <Duct_SectionFormI.hxx>

#endif // !_Duct_SectionForm_Header
