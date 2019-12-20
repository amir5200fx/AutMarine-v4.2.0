#pragma once
#ifndef _FvmMesh_ElementIndex_Header
#define _FvmMesh_ElementIndex_Header

#include <Global_Memory.hxx>
#include <Standard_IStream.hxx>

namespace AutLib
{
	namespace FvmLib
	{

		class FvmMesh_ElementIndex
		{

		private:


		public:

			FvmMesh_ElementIndex();

			friend Standard_IStream& operator>>(Standard_IStream&, Global_Handle(FvmMesh_ElementIndex)& theObject);
		};
	}
}

#endif // !_FvmMesh_ElementIndex_Header
