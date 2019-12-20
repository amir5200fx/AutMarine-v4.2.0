#pragma once
#ifndef _Prop_PitchForm_Header
#define _Prop_PitchForm_Header

#include <Standard_Real.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Prop_PitchForm
		{

		private:

			Standard_Real theRootPitch_;
			Standard_Real theRootSteep_;
			Standard_Real theTipPitch_;
			Standard_Real theTipSteep_;

		public:

			Prop_PitchForm();

			Standard_Real RootPitch() const;

			Standard_Real RootSteep() const;

			Standard_Real TipPitch() const;

			Standard_Real TipSteep() const;

			void SetRootPitch(const Standard_Real RootPitch);

			void SetRootSteep(const Standard_Real RootSteep);

			void SetTipPitch(const Standard_Real TipPitch);

			void SetTipSteep(const Standard_Real TipSteep);
		};
	}
}

#include <Prop_PitchFormI.hxx>

#endif // !_Prop_PitchForm_Header
