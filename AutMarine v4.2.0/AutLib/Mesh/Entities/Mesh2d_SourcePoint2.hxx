#pragma once
#ifndef _Mesh2d_SourcePoint2_Header
#define _Mesh2d_SourcePoint2_Header

#include <Mesh2d_SourcePoint.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh2d_SourcePoint2 : public Mesh2d_SourcePoint
		{

		private:

			Standard_Real theRadius_;

		public:

			Mesh2d_SourcePoint2();

			Mesh2d_SourcePoint2(const Geom_Pnt2d& theCoord, const Standard_Real theValue, const Standard_Real theRadius);

			virtual ~Mesh2d_SourcePoint2() {}

			void Init(const Geom_Pnt2d& theCoord, const Standard_Real theValue, const Standard_Real theRadius);

			void SetRadius(const Standard_Real theRadius);

			Standard_Real Radius() const;
		};
	}
}

#include <Mesh2d_SourcePoint2I.hxx>

#endif // !_Mesh2d_SourcePoint2_Header
