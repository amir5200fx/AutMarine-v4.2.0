#pragma once
#ifndef _FvGeom_ElementConnectivity2d_Header
#define _FvGeom_ElementConnectivity2d_Header

#include <Standard_TypeDef.hxx>
#include <Standard_Stream.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvGeom_ElementConnectivity2d
		{

		private:


		public:

			virtual Standard_Integer Size() const = 0;

			virtual Standard_Integer Value(const Standard_Integer theIndex) const = 0;

			virtual void Import(fstream& File) = 0;

		protected:

			FvGeom_ElementConnectivity2d();
		};
	}
}

#endif // !_FvGeom_ElementConnectivity2d_Header

