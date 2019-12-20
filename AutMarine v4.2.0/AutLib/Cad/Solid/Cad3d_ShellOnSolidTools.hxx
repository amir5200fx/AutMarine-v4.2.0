#pragma once
#ifndef _Cad3d_ShellOnSolidTools_Header
#define _Cad3d_ShellOnSolidTools_Header

#include <TColCad3d_HAry1dOfSurfaceOnSolid.hxx>
#include <TColCad3d_HAry1dOfShellOnSolid.hxx>
#include <Cad3d_InnerBoundariesOnSolid.hxx>
#include <Cad3d_OutterBoundaryOnSolid.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Cad3d_ShellOnSolidTools
		{

		public:

			static Standard_Boolean IsLess(Global_Handle(Cad3d_ShellOnSolid) const& theShell1, Global_Handle(Cad3d_ShellOnSolid) const& theShell2);

			static Standard_Boolean IdentifyBoundaries(const TColCad3d_HAry1dOfShellOnSolid& theShells, Cad3d_InnerBoundariesOnSolid& theInner, Cad3d_OutterBoundaryOnSolid& theOutter);

			static TColCad3d_HAry1dOfShellOnSolid TrackShells(const TColCad3d_HAry1dOfSurfaceOnSolid& theSurfaces);

			static void SortOrientation(Cad3d_ShellOnSolid& theShell);

		};
	}
}

#endif // !_Cad3d_ShellOnSolidTools_Header
