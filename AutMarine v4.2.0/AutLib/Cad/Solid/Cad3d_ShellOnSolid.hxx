#pragma once
#ifndef _Cad3d_ShellOnSolid_Header
#define _Cad3d_ShellOnSolid_Header

#include <Entity_Box3d.hxx>
#include <TColCad3d_HAry1dOfSurfaceOnSolid.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Cad3d_ShellOnSolid
		{

		private:

			Standard_Integer theIndex_;

			TColCad3d_HAry1dOfSurfaceOnSolid theSurfaces_;

			M_GEO Entity_Box3d theBox_;



		public:

			Cad3d_ShellOnSolid();

			Cad3d_ShellOnSolid(const Standard_Integer theIndex, const TColCad3d_HAry1dOfSurfaceOnSolid& theSurfaces);

			void Init(const Standard_Integer theIndex, const TColCad3d_HAry1dOfSurfaceOnSolid& theSurfaces);

			void SetIndex(const Standard_Integer theIndex);

			const TColCad3d_HAry1dOfSurfaceOnSolid& Surfaces() const;

			Standard_Integer NbSurfaces() const;

			Standard_Integer Index() const;

			Standard_Boolean IsClosed() const;

			const M_GEO Entity_Box3d& BoundingBox() const;

			void ExportToPlt(fstream& File) const;

		private:

			void CalcBoundingBox();
		};
	}
}

#include <Cad3d_ShellOnSolidI.hxx>

#endif // !_Cad3d_ShellOnSolid_Header
