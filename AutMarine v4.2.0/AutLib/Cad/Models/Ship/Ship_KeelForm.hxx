#pragma once
#ifndef _Ship_KeelForm_Header
#define _Ship_KeelForm_Header

#include <Standard_TypeDef.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Ship_KeelForm
		{

		private:

			Standard_Real KeelPosition_;
			Standard_Real KeelRisePoint_;
			Standard_Real KeelRiseTangent_;
			Standard_Real KeelTransomTangent_;

		public:

			Ship_KeelForm();

			void SetKeelPosition(const Standard_Real Value);

			void SetKeelRisePoint(const Standard_Real Value);

			void SetKeelRiseTangent(const Standard_Real Value);

			void SetKeelTransomTangent(const Standard_Real Value);

			Standard_Real KeelPosition() const;

			Standard_Real KeelRisePoint() const;

			Standard_Real KeelRiseTangent() const;

			Standard_Real KeelTransomTangent() const;
		};
	}
}

#endif // !_Ship_KeelForm_Header
