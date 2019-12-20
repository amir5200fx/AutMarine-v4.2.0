#pragma once
#ifndef _Prop_SkewForm_Header
#define _Prop_SkewForm_Header

#include <Standard_Real.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Prop_SkewForm
		{

		private:

			Standard_Real theTipSkew_;
			Standard_Real theTipSteep_;
			Standard_Real theRootSteep_;

		public:

			Prop_SkewForm();

			Standard_Real TipSkew() const;

			Standard_Real TipSteep() const;

			Standard_Real RootSteep() const;

			void SetTipSkew(const Standard_Real Value);

			void SetTipSteep(const Standard_Real Value);

			void SetRootSteep(const Standard_Real Value);
		};
	}
}

#include <Prop_SkewFormI.hxx>

#endif // !_Prop_SkewForm_Header
