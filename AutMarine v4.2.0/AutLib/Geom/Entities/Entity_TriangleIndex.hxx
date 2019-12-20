#pragma once
#ifndef _Entity_TriangleIndex_Header
#define _Entity_TriangleIndex_Header

#include <Standard_Integer.hxx>
#include <Standard_OStream.hxx>
#include <Standard_IStream.hxx>
#include <Global_Debug.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Entity_TriangleIndex
		{

		private:

			Standard_Integer theValue_[3];

		public:

			Entity_TriangleIndex();

			Entity_TriangleIndex(const Standard_Integer V0, const Standard_Integer V1, const Standard_Integer V2);

			Standard_Integer& Value(const Standard_Integer Index);

			Standard_Integer Value(const Standard_Integer Index) const;

			Standard_Integer V0() const;

			Standard_Integer V1() const;

			Standard_Integer V2() const;

			Standard_Integer &V0();

			Standard_Integer &V1();

			Standard_Integer &V2();

			void SetV0(const Standard_Integer Value);

			void SetV1(const Standard_Integer Value);

			void SetV2(const Standard_Integer Value);

			void SetValue(const Standard_Integer V0, const Standard_Integer V1, const Standard_Integer V2);

			friend Standard_OStream& operator<<(Standard_OStream& Os, const Entity_TriangleIndex& Triangle);

			friend Standard_IStream& operator>>(Standard_IStream& Is, Entity_TriangleIndex& Triangle);
		};
	}
}

#include <Entity_TriangleIndexI.hxx>

#endif // !_Entity_TriangleIndex_Header
