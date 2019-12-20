#pragma once
#ifndef _Entity_TetrahedronIndex_Header
#define _Entity_TetrahedronIndex_Headeer

#include <Standard_Integer.hxx>
#include <Standard_OStream.hxx>
#include <Standard_IStream.hxx>
#include <Global_Debug.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Entity_TetrahedronIndex
		{

		private:

			Standard_Integer theValue_[4];

		public:

			Entity_TetrahedronIndex();

			Entity_TetrahedronIndex(const Standard_Integer V0, const Standard_Integer V1, const Standard_Integer V2, const Standard_Integer V3);

			Standard_Integer& Value(const Standard_Integer Index);

			Standard_Integer Value(const Standard_Integer Index) const;

			Standard_Integer V0() const;

			Standard_Integer V1() const;

			Standard_Integer V2() const;

			Standard_Integer V3() const;

			Standard_Integer &V0();

			Standard_Integer &V1();

			Standard_Integer &V2();

			Standard_Integer &V3();

			void SetV0(const Standard_Integer Value);

			void SetV1(const Standard_Integer Value);

			void SetV2(const Standard_Integer Value);

			void SetV3(const Standard_Integer Value);

			void SetValue(const Standard_Integer V0, const Standard_Integer V1, const Standard_Integer V2, const Standard_Integer V3);

			void GetValue(Standard_Integer& V0, Standard_Integer& V1, Standard_Integer& V2, Standard_Integer& V3) const;

			friend Standard_OStream& operator<<(Standard_OStream& Os, const Entity_TetrahedronIndex& Tet);

			friend Standard_IStream& operator>>(Standard_IStream& Is, Entity_TetrahedronIndex& Tet);
		};
	}
}

#include <Entity_TetrahedronIndexI.hxx>

#endif // !_Entity_TetrahedronIndex_Header

