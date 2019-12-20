#pragma once
#ifndef _FvmMesh_TriangleIndex_Header
#define _FvmMesh_TriangleIndex_Header

#include <Standard_TypeDef.hxx>
#include <Standard_IStream.hxx>
#include <Standard_OStream.hxx>
#include <Global_Debug.hxx>
#include <FvmMesh_ElementIndex.hxx>

namespace AutLib
{
	namespace FvmLib
	{

		class FvmMesh_TriangleIndex : public FvmMesh_ElementIndex
		{

		private:

			Standard_Integer theValue_[3];

		public:

			FvmMesh_TriangleIndex();

			FvmMesh_TriangleIndex(const Standard_Integer theV0, const Standard_Integer theV1, const Standard_Integer theV2);

			void Init(const Standard_Integer theV0, const Standard_Integer theV1, const Standard_Integer theV2);

			void SetV0(const Standard_Integer theIndex);

			void SetV1(const Standard_Integer theIndex);

			void SetV2(const Standard_Integer theIndex);

			Standard_Integer V0() const;

			Standard_Integer V1() const;

			Standard_Integer V2() const;

			Standard_Integer Value(const Standard_Integer theIndex) const;

			friend Standard_IStream& operator>>(Standard_IStream& Istream, FvmMesh_TriangleIndex& theObject);
		};
	}
}

#include <FvmMesh_TriangleIndexI.hxx>

#endif // !_FvmMesh_TriangleIndex_Header
