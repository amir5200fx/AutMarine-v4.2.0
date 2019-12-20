#pragma once
#ifndef _FvmMesh_Node2d_Header
#define _FvmMesh_Node2d_Header

#include <Geom_Pnt2d.hxx>

namespace AutLib
{
	namespace FvmLib
	{

		class FvmMesh_Node2d
		{

		private:

			Geom_Pnt2d theCoord_;

			Standard_Integer theIndex_;

		public:

			FvmMesh_Node2d();

			FvmMesh_Node2d(const Standard_Integer theIndex, const Geom_Pnt2d& theCoord);

			void Init(const Standard_Integer theIndex, const Geom_Pnt2d& theCoord);

			void SetIndex(const Standard_Integer theIndex);

			void SetCoord(const Geom_Pnt2d& theCoord);

			Standard_Integer Index() const;

			const Geom_Pnt2d& Coord() const;
		};
	}
}

#include <FvmMesh_Node2dI.hxx>

#endif // !_FvmMesh_Node2d_Header
