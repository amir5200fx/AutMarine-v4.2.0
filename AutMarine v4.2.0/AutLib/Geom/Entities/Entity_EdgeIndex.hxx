#pragma once
#ifndef _Entity_EdgeIndex_Header
#define _Entity_EdgeIndex_Header

#include <Standard_Integer.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Entity_EdgeIndex
		{

		private:

			Standard_Integer theValue_[2];

		public:

			Entity_EdgeIndex();

			Entity_EdgeIndex(const Standard_Integer V1, const Standard_Integer V2);

			Standard_Integer Value(const Standard_Integer Index) const;

			Standard_Integer& ChangeValue(const Standard_Integer);

			Standard_Integer V0() const;

			Standard_Integer V1() const;

			Standard_Integer& V0();

			Standard_Integer& V1();

			void Reverse();

			void SetValue(const Standard_Integer Index, const Standard_Integer Value);

			void SetV12(const Standard_Integer V1, const Standard_Integer V2);
		};
	}
}

#include <Entity_EdgeIndexI.hxx>

#endif // !_Entity_EdgeIndex_Header
