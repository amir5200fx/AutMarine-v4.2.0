#pragma once
#ifndef _Entity_Box2d_Header
#define _Entity_Box2d_Header

#include <Standard_Real.hxx>
#include <Standard_OStream.hxx>
#include <Geom_Pnt2d.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Entity_Box2d
		{

		private:

			Standard_Real xmin_;
			Standard_Real xmax_;
			Standard_Real ymin_;
			Standard_Real ymax_;

		public:

			Entity_Box2d();

			Entity_Box2d(const Standard_Real Xmin, const Standard_Real Xmax, const Standard_Real Ymin, const Standard_Real Ymax);

			Standard_Real Xmin() const;

			Standard_Real Xmax() const;

			Standard_Real Ymin() const;

			Standard_Real Ymax() const;

			Standard_Real& Xmin();

			Standard_Real& Xmax();

			Standard_Real& Ymin();

			Standard_Real& Ymax();

			Entity_Box2d NwQuarter() const;

			Entity_Box2d NeQuarter() const;

			Entity_Box2d SwQuarter() const;

			Entity_Box2d SeQuarter() const;

			Entity_Box2d LeftHalf() const;

			Entity_Box2d RightHalf() const;

			Entity_Box2d UpHalf() const;

			Entity_Box2d DownHalf() const;

			Entity_Box2d OffsetBox(const Standard_Real Tolerance) const;

			Geom_Pnt2d CalcCentre() const;

			Geom_Pnt2d GetNwPoint() const;

			Geom_Pnt2d GetNePoint() const;

			Geom_Pnt2d GetSwPoint() const;

			Geom_Pnt2d GetSePoint() const;

			Standard_Real Diameter() const;

			Standard_Real DiameterSQ() const;

			void Exapnd(const Standard_Real theValue);

			void Get(Standard_Real& theXmin, Standard_Real& theXmax, Standard_Real& theYmin, Standard_Real& theYmax) const;

			void Print(Standard_OStream& Ostream = cout) const;

			void ExportToPlt(fstream& File) const;
		};
	}
}

#include <Entity_Box2dI.hxx>

#endif // !_Entity_Box2d_Header
