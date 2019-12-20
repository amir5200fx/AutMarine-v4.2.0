#pragma once
#ifndef _Cad3d_EdgeOnSolidTools_Header
#define _Cad3d_EdgeOnSolidTools_Header

#include <Cad3d_EdgeOnSolid.hxx>
#include <TColCad3d_HAry1dOfSurfaceOnSolid.hxx>
#include <TColCad3d_HAry1dOfEdgeOnSolid.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Cad3d_EdgeOnSolidTools
		{

		public:

			static Standard_Boolean IsLess(Global_Handle(Cad3d_EdgeOnSolid) const & theEdge1, Global_Handle(Cad3d_EdgeOnSolid) const & theEdge2);

			static Standard_Boolean CheckForConfomity(const Cad3d_EdgeOnSolid& theEdge, const Standard_Real Tolerance);

			static Standard_Boolean CheckForConfomityWithDirection(const Cad3d_EdgeOnSolid& theEdge, const Standard_Real Tolerance);

			static Standard_Boolean IsSameDirection(const Cad3d_EdgeOnSolid& theEdge0, const Cad3d_EdgeOnSolid& theEdge1);

			static TColCad3d_HAry1dOfEdgeOnSolid RetrieveEdgesFrom(const TColCad3d_HAry1dOfSurfaceOnSolid& theSurfaces);
		};
	}
}

#include <Cad3d_EdgeOnSolidToolsI.hxx>

#endif // !_Cad3d_EdgeOnSolidTools_Header
