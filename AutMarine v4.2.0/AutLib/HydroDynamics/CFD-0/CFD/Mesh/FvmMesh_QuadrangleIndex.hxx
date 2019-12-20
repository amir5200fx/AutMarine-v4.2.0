#pragma once
#ifndef _FvmMesh_QuadrangleIndex_Header
#define _FvmMesh_QuadrangleIndex_Header

#include <Standard_TypeDef.hxx>
#include <Standard_IStream.hxx>
#include <Standard_OStream.hxx>
#include <Global_Debug.hxx>
#include <FvmMesh_ElementIndex.hxx>

namespace AutLib
{
	namespace FvmLib
	{

		class FvmMesh_QuadrangleIndex : public FvmMesh_ElementIndex
		{

		private:

			Standard_Integer theValue_[4];

		public:

			FvmMesh_QuadrangleIndex();

			FvmMesh_QuadrangleIndex(const Standard_Integer theV0, const Standard_Integer theV1, const Standard_Integer theV2, const Standard_Integer theV3);

			void Init(const Standard_Integer theV0, const Standard_Integer theV1, const Standard_Integer theV2, const Standard_Integer theV3);

			void SetV0(const Standard_Integer theIndex);

			void SetV1(const Standard_Integer theIndex);

			void SetV2(const Standard_Integer theIndex);

			void SetV3(const Standard_Integer theIndex);

			void SetValue(const Standard_Integer theIndex, const Standard_Integer theValue);

			Standard_Integer V0() const;

			Standard_Integer V1() const;

			Standard_Integer V2() const;

			Standard_Integer V3() const;

			Standard_Integer Value(const Standard_Integer theIndex) const;

			friend Standard_IStream& operator >> (Standard_IStream& Istream, FvmMesh_QuadrangleIndex& theObject);
		};
	}
}

#include <FvmMesh_QuadrangleIndexI.hxx>

#endif // !_FvmMesh_QuadrangleIndex_Header
