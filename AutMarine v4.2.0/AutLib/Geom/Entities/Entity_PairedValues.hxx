#pragma once
#ifndef _Entity_PairedValues_Header
#define _Entity_PairedValues_Header

namespace AutLib
{
	namespace GeoLib
	{

		template<typename T>
		class Entity_PairedValues
		{

		private:

			T theX1_;
			T theX2_;

		public:

			Entity_PairedValues();

			Entity_PairedValues(T theX1, T theX2);

			T X1() const;

			T X2() const;

			T& X1();

			T& X2();
		};
	}
}

#include <Entity_PairedValuesI.hxx>

#endif // !_Entity_PairedValues_Header
