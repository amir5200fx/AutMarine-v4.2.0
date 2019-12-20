#pragma once
#ifndef _Prop_HubForm_Header
#define _Prop_HubForm_Header

#include <Standard_TypeDef.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Prop_HubForm
		{

		private:

			Standard_Real theHubLength_;
			Standard_Real theHubWeight_;
			Standard_Real theShaftRadius_;
			Standard_Real theShaftOffset_;
			Standard_Real theShaftLenght_;

		public:

			Prop_HubForm();

			Standard_Real HubLength() const;

			Standard_Real HubWeight() const;

			Standard_Real ShaftRadius() const;

			Standard_Real ShaftOffset() const;

			Standard_Real ShaftLength() const;

			void SetHubLength(const Standard_Real theValue);

			void SetHubWeight(const Standard_Real theValue);

			void SetShaftRadius(const Standard_Real theValue);

			void SetShaftOffset(const Standard_Real theValue);

			void SetShaftLength(const Standard_Real theValue);
		};
	}
}

#include <Prop_HubFormI.hxx>

#endif // !_Prop_HubForm_Header
