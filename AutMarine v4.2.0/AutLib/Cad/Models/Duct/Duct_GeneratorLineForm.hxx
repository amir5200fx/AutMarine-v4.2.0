#pragma once
#ifndef _Duct_GeneratorLineForm_Header
#define _Duct_GeneratorLineForm_Header

#include <Standard_TypeDef.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Duct_GeneratorLineForm
		{

		private:

			Standard_Real thePosition_;
			Standard_Real theRisePoint_;
			Standard_Real theRiseTangent_;
			Standard_Real theOutletTangent_;

		public:

			Duct_GeneratorLineForm();

			void SetPosition(const Standard_Real Value);

			void SetRisePoint(const Standard_Real Value);

			void SetRiseTangent(const Standard_Real Value);

			void SetOutletTangent(const Standard_Real Value);

			Standard_Real Position() const;

			Standard_Real RisePoint() const;

			Standard_Real RiseTangent() const;

			Standard_Real OutletTangent() const;
		};
	}
}

#include <Duct_GeneratorLineFormI.hxx>

#endif // !_Duct_GeneratorLineForm_Header
