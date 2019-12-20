#pragma once
#ifndef _Prop_CamberForm_Header
#define _Prop_CamberForm_Header

#include <Standard_Real.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Prop_CamberForm
		{

		private:

			Standard_Real theRootCamber_;
			Standard_Real theTipCamber_;

			Standard_Real theMaxCamber_;
			Standard_Real theMaxCamberLocation_;

			Standard_Real theRootWeight_;
			Standard_Real theTipWeight_;

		public:

			Prop_CamberForm();

			Standard_Real RootCamber() const;

			Standard_Real TipCamber() const;

			Standard_Real MaxCamber() const;

			Standard_Real MaxCamberLocation() const;

			Standard_Real RootWeight() const;

			Standard_Real TipWeight() const;

			void SetRootCamber(const Standard_Real Value);

			void SetTipCamber(const Standard_Real Value);

			void SetMaxCamber(const Standard_Real Value);

			void SetMaxCamberLocation(const Standard_Real Value);

			void SetRootWeight(const Standard_Real Value);

			void SetTipWeight(const Standard_Real Value);
		};
	}
}

#include <Prop_CamberFormI.hxx>

#endif // !_Prop_CamberForm_Header
