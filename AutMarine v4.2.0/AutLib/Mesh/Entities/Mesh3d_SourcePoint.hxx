#pragma once
#ifndef _Mesh3d_SourcePoint_Header
#define _Mesh3d_SourcePoint_Header

#include <Geom_Pnt3d.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_SourcePoint
		{

		private:

			Geom_Pnt3d theCoord_;

			Standard_Real theValue_;

		public:

			Mesh3d_SourcePoint();

			Mesh3d_SourcePoint(const Geom_Pnt3d& theCoord, const Standard_Real Value);

			void Init(const Geom_Pnt3d& theCoord, const Standard_Real Value);

			void SetCoord(const Geom_Pnt3d& theCoord);

			void SetValue(const Standard_Real Value);

			const Geom_Pnt3d& Coord() const;

			Standard_Real Value() const;
		};
	}
}

#include <Mesh3d_SourcePointI.hxx>

#endif // !_Mesh3d_SourcePoint_Header
