#pragma once
#ifndef _Duct_HullForm_Header
#define _Duct_HullForm_Header

#include <Duct_SectionForm.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Duct_HullForm
		{

		private:

			Duct_SectionForm theInletForm_;
			Duct_SectionForm theMidForm_;
			Duct_SectionForm theOutletForm_;

			Standard_Real theMidLocation_;

		public:

			Duct_HullForm();

			void SetInletForm(const Duct_SectionForm& theInletForm);

			void SetOutletForm(const Duct_SectionForm& theOutletForm);

			void SetMidForm(const Duct_SectionForm& theMidForm);

			void SetMidLocation(const Standard_Real theMidLocation);

			Duct_SectionForm& InletForm();

			Duct_SectionForm& MidForm();

			Duct_SectionForm& OutletForm();

			const Duct_SectionForm& InletForm() const;

			const Duct_SectionForm& OutletForm() const;

			const Duct_SectionForm& MidForm() const;

			Standard_Real MidLocation() const;
		};
	}
}

#include <Duct_HullFormI.hxx>

#endif // !_Duct_HullForm_Header
