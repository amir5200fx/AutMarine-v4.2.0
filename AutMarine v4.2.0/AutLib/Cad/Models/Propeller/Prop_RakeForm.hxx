#pragma once
#ifndef _Prop_RakeForm_Header
#define _Prop_RakeForm_Header

#include <Standard_Real.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Prop_RakeForm
		{

		private:

			Standard_Real theTipRake_;

		public:

			Prop_RakeForm();

			Standard_Real TipRake() const;

			void SetTipRake(const Standard_Real Value);
		};
	}
}

#include <Prop_RakeFormI.hxx>

#endif // !_Prop_RakeForm_Header
