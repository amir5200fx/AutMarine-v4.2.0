#pragma once
#ifndef _FvParameters_TimeConfig_Header
#define _FvParameters_TimeConfig_Header

#include <Standard_TypeDef.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvParameters_TimeConfig
		{

		private:

			Standard_Real theStart_;
			Standard_Real theEnd_;
			

		public:

			virtual ~FvParameters_TimeConfig();

			Standard_Real Start() const;

			Standard_Real End() const;

			void SetStart(const Standard_Real theValue);

			void SetEnd(const Standard_Real theValue);

			virtual Standard_Real Step() const = 0;

		protected:

			FvParameters_TimeConfig();
		};
	}
}

#include <FvParameters_TimeConfigI.hxx>

#endif // !_FvParameters_TimeConfig_Header
