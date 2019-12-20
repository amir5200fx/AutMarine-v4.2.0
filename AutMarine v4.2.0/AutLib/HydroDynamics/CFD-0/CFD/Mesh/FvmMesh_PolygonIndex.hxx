#pragma once
#ifndef _FvmMesh_PolygonIndex_Header
#define _FvmMesh_PolygonIndex_Header

#include <Standard_TypeDef.hxx>
#include <Standard_IStream.hxx>
#include <Standard_OStream.hxx>
#include <Global_Debug.hxx>
#include <FvmMesh_ElementIndex.hxx>
#include <TColStd_Ary1dOfInteger.hxx>

namespace AutLib
{
	namespace FvmLib
	{

		class FvmMesh_PolygonIndex : public FvmMesh_ElementIndex
		{

		private:

			TColStd_Ary1dOfInteger theValue_;

		public:

			FvmMesh_PolygonIndex();

			FvmMesh_PolygonIndex(const TColStd_Ary1dOfInteger& theValue);

			void Init(const TColStd_Ary1dOfInteger& theValue);

			void SetValue(const Standard_Integer theIndex, const Standard_Integer theValue);

			Standard_Integer Size() const;

			Standard_Integer Value(const Standard_Integer theIndex) const;

			const TColStd_Ary1dOfInteger& Value() const;

			friend Standard_IStream& operator>>(Standard_IStream& Istream, FvmMesh_PolygonIndex& theObject);
		};
	}
}

#include <FvmMesh_PolygonIndexI.hxx>

#endif // !_FvmMesh_PolygonIndex_Header
