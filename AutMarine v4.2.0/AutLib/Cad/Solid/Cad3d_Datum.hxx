#pragma once
#ifndef _Cad3d_Datum_Header
#define _Cad3d_Datum_Header

#include <Standard_String.hxx>
#include <Geom_Pnt3d.hxx>

class gp_Trsf;

namespace AutLib
{
	namespace CadLib
	{

		class Cad3d_Datum
		{

		private:

			Geom_Pnt3d theCoord_;

			Standard_String theName_;

		public:

			Cad3d_Datum();

			Cad3d_Datum(const Geom_Pnt3d& theCoord, const Standard_String theName);

			void Init(const Geom_Pnt3d& theCoord, const Standard_String theName);

			void SetCoord(const Geom_Pnt3d& theCoord);

			void SetName(const Standard_String theName);

			void Transform(const gp_Trsf& theTrsf);

			const Geom_Pnt3d& Coord() const;

			const Standard_String& Name() const;
		};
	}
}

#include <Cad3d_DatumI.hxx>

#endif // !_Cad3d_Datum_Header
