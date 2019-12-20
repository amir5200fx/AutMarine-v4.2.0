#pragma once
#ifndef _Ship_TransomForm_Header
#define _Ship_TransomForm_Header

#include <Standard_TypeDef.hxx>
#include <Standard_OStream.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Ship_TransomForm
		{

		private:

			Standard_Real theRake_;
			Standard_Real theWidth_;

		public:

			Ship_TransomForm();

			void SetRake(const Standard_Real Value);

			void SetWidth(const Standard_Real Value);

			Standard_Real Rake() const;

			Standard_Real Width() const;

			void Print(Standard_OStream& Stream = cout) const;
		};
	}
}

#endif // !_Ship_TransomForm_Header
