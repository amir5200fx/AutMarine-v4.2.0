#pragma once
#ifndef _Mesh2d_SourcePoint_Header
#define _Mesh2d_SourcePoint_Header

#include <Geom_Pnt2d.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh2d_SourcePoint
		{

		protected:

			Geom_Pnt2d theCoord_;

			Standard_Real theValue_;

		public:

			Mesh2d_SourcePoint();

			Mesh2d_SourcePoint(const Geom_Pnt2d& theCoord, const Standard_Real theValue);

			virtual ~Mesh2d_SourcePoint() {}

			void Init(const Geom_Pnt2d& theCoord, const Standard_Real theValue);

			void SetCoord(const Geom_Pnt2d& theCoord);

			void SetValue(const Standard_Real Value);

			const Geom_Pnt2d& Coord() const;

			Standard_Real Value() const;
		};
	}
}

#include <Mesh2d_SourcePointI.hxx>

#endif // !_Mesh2d_SourcePoint_Header
