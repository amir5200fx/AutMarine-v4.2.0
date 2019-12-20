#pragma once
#ifndef _Entity_TetrahedralizationTools_Header
#define _Entity_TetrahedralizationTools_Header

#include <Standard_Type.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Entity_Tetrahedralization;

		class Entity_TetrahedralizationTools
		{

		public:

			static void xCoord_Split(const Standard_Real theX, const Entity_Tetrahedralization& theTetrahedralization, Entity_Tetrahedralization& theLeft, Entity_Tetrahedralization& theRight);

			static void yCoord_Split(const Standard_Real theY, const Entity_Tetrahedralization& theTetrahedralization, Entity_Tetrahedralization& theLeft, Entity_Tetrahedralization& theRight);

			static void zCoord_Split(const Standard_Real theZ, const Entity_Tetrahedralization& theTetrahedralization, Entity_Tetrahedralization& theLeft, Entity_Tetrahedralization& theRight);
		};
	}
}

#endif // !_Entity_TetrahedralizationTools_Header
