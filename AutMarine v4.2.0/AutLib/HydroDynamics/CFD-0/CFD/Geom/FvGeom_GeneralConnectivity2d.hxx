#pragma once
#ifndef _FvGeom_GeneralConnectivity2d_Header
#define _FvGeom_GeneralConnectivity2d_Header

#include <FvGeom_ElementConnectivity2d.hxx>
#include <TColStd_Ary1dOfInteger.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvGeom_GeneralConnectivity2d : public FvGeom_ElementConnectivity2d
		{

		private:

			TColStd_Ary1dOfInteger theValues_;

		public:

			FvGeom_GeneralConnectivity2d();

			virtual Standard_Integer Size() const;

			virtual Standard_Integer Value(const Standard_Integer theIndex) const;

			virtual void Import(fstream& File);
		};
	}
}

#include <FvGeom_GeneralConnectivity2dI.hxx>

#endif // !_FvGeom_GeneralConnectivity2d_Header
