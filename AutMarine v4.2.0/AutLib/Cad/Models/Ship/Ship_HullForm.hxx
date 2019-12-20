#pragma once
#ifndef _Ship_HullForm_Header
#define _Ship_HullForm_Header

#include <Ship_SectionForm.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Ship_HullForm
		{

		private:

			Ship_SectionForm AftForm_;
			Ship_SectionForm MidForm_;
			Ship_SectionForm FwdForm_;

			Standard_Real MaxAreaLocation_;
			//Standard_Real PrismaticControl_;

			Standard_Real SheerHeight_;
			Standard_Real SheerPosition_;

			Standard_Real FullnessFwd_;
			Standard_Real FullnessAft_;

		public:

			Ship_HullForm();

			void SetAftForm(const Ship_SectionForm& AftForm);

			void SetMidForm(const Ship_SectionForm& MidForm);

			void SetFwdForm(const Ship_SectionForm& FwdForm);

			void SetMaxAreaLocation(const Standard_Real MaxAreaLocation);

			void SetSheerHeight(const Standard_Real SheerHeight);

			void SetSheerPosition(const Standard_Real SheerPosition);

			void SetFullnessFwd(const Standard_Real FullnessFwd);

			void SetFullnessAft(const Standard_Real FullnessAft);

			Ship_SectionForm& AftForm();

			Ship_SectionForm& MidForm();

			Ship_SectionForm& FwdForm();

			const Ship_SectionForm& AftForm() const;

			const Ship_SectionForm& MidForm() const;

			const Ship_SectionForm& FwdForm() const;

			Standard_Real MaxAreaLocation() const;

			Standard_Real SheerHeight() const;

			Standard_Real SheerPosition() const;

			Standard_Real FullnessFwd() const;

			Standard_Real FullnessAft() const;
		};
	}
}

#endif // !_Ship_HullForm_Header
