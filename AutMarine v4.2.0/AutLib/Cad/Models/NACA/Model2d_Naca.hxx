#pragma once
#ifndef _Model2d_Naca_Header
#define _Model2d_Naca_Header

#include <Standard_Handle.hxx>
#include <Standard_Stream.hxx>

class Geom2d_Curve;

namespace AutLib
{
	namespace CadLib
	{

		class Model2d_Naca
		{

		protected:

			Handle(Geom2d_Curve) theUpper_;
			Handle(Geom2d_Curve) theLower_;

		public:

			//! Warning: The Curve must be deleted to release the memory
			Handle(Geom2d_Curve) UpperCurve() const;

			//! Warning: The Curve must be deleted to release the memory
			Handle(Geom2d_Curve) LowerCurve() const;

			void ExportToPlt(fstream& File) const;

		protected:

			Model2d_Naca();

			virtual void Perform() = 0;
		};
	}
}

#include <Model2d_NacaI.hxx>

#endif // !_Model2d_Naca_Header
