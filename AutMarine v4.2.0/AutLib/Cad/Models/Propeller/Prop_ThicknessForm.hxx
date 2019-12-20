#pragma once
#ifndef _Prop_ThicknessForm_Header
#define _Prop_ThicknessForm_Header

#include <Standard_Real.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Prop_ThicknessForm
		{

		private:

			Standard_Real theRootThickness_;
			Standard_Real theTipThickness_;
			Standard_Real theRootSteep_;
			Standard_Real theTipSteep_;

		public:

			Prop_ThicknessForm();

			Standard_Real RootThickness() const;

			Standard_Real TipThickness() const;

			Standard_Real RootSteep() const;

			Standard_Real TipSteep() const;

			void SetRootThickness(const Standard_Real Value);

			void SetTipThickness(const Standard_Real Value);

			void SetRootSteep(const Standard_Real Value);

			void SetTipSteep(const Standard_Real Value);
		};
	}
}

#include <Prop_ThicknessFormI.hxx>

#endif // !_Prop_ThicknessForm_Header
