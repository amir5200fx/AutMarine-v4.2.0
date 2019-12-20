#pragma once
#ifndef _Ship_SectionForm_Header
#define _Ship_SectionForm_Header

#include <Standard_TypeDef.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Ship_SectionForm
		{

		private:

			Standard_Real theTightness_;
			Standard_Real theDeadRise_;
			Standard_Real theSideSlope_;
			Standard_Real theFlare_;
			Standard_Real theskeg_;

		public:

			Ship_SectionForm();

			void SetTightness(const Standard_Real Value);

			void SetDeadRise(const Standard_Real Value);

			void SetSideSlope(const Standard_Real Value);

			void SetFlare(const Standard_Real Value);

			void SetSkeg(const Standard_Real Value);

			Standard_Real Tightness() const;

			Standard_Real DeadRise() const;

			Standard_Real SideSlope() const;

			Standard_Real Flare() const;

			Standard_Real Skeg() const;
		};
	}
}

#endif // !_Ship_SectionForm_Header
