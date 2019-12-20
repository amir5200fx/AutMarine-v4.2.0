#pragma once
#ifndef _Entity_Box3d_Header
#define _Entity_Box3d_Header

#include <Geom_Pnt3d.hxx>
#include <Standard_OStream.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Entity_Box3d
		{

		private:

			Standard_Real theXmin_;
			Standard_Real theXmax_;
			Standard_Real theYmin_;
			Standard_Real theYmax_;
			Standard_Real theZmin_;
			Standard_Real theZmax_;

		public:

			Entity_Box3d();

			Entity_Box3d(const Standard_Real Xmin, const Standard_Real Xmax, const Standard_Real Ymin, const Standard_Real Ymax, const Standard_Real Zmin, const Standard_Real Zmax);

			Entity_Box3d(const Geom_Pnt3d& MinCorner, const Geom_Pnt3d& MaxCorner);

			Standard_Real Xmin() const;

			Standard_Real Xmax() const;

			Standard_Real Ymin() const;

			Standard_Real Ymax() const;

			Standard_Real Zmin() const;

			Standard_Real Zmax() const;

			Standard_Real& Xmin();

			Standard_Real& Xmax();

			Standard_Real& Ymin();

			Standard_Real& Ymax();

			Standard_Real& Zmin();

			Standard_Real& Zmax();

			Entity_Box3d Fwd_NwOctant() const;

			Entity_Box3d Fwd_NeOctant() const;

			Entity_Box3d Fwd_SwOctant() const;

			Entity_Box3d Fwd_SeOctant() const;

			Entity_Box3d Bwd_NwOctant() const;

			Entity_Box3d Bwd_NeOctant() const;

			Entity_Box3d Bwd_SwOctant() const;

			Entity_Box3d Bwd_SeOctant() const;

			Entity_Box3d LeftHalf() const;

			Entity_Box3d RightHalf() const;

			Entity_Box3d UpHalf() const;

			Entity_Box3d DownHalf() const;

			Entity_Box3d FwdHalf() const;

			Entity_Box3d BwdHalf() const;

			Entity_Box3d OffsetBox(const Standard_Real Tolerance) const;

			void InitUnitBox();

			Geom_Pnt3d CalcCentre() const;

			Geom_Pnt3d Fwd_NwCorner() const;

			Geom_Pnt3d Fwd_NeCorner() const;

			Geom_Pnt3d Fwd_SwCorner() const;

			Geom_Pnt3d Fwd_SeCorner() const;

			Geom_Pnt3d Bwd_NwCorner() const;

			Geom_Pnt3d Bwd_NeCorner() const;

			Geom_Pnt3d Bwd_SwCorner() const;

			Geom_Pnt3d Bwd_SeCorner() const;

			Standard_Real Diameter() const;

			Standard_Real DiameterSQ() const;

			void Expand(const Standard_Real Offset);

			void Print(Standard_OStream& Ostream = cout) const;

			void ExportToPlt(fstream& File) const;
		};
	}
}

#include <Entity_Box3dI.hxx>

#endif // !_Entity_Box3d_Header
