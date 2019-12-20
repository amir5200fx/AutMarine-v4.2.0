#pragma once
#ifndef _Mesh3d_Ship_Header
#define _Mesh3d_Ship_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <Standard_TypeDef.hxx>

namespace AutLib
{

	namespace CadLib
	{
		class Compound_Ship;
	}

	namespace MeshLib
	{

		
		class Mesh3d_Region;
		class Mesh_ReferenceValues;

		class Mesh3d_Ship
		{

		private:

			Global_Handle(M_CAD Compound_Ship) theShip_;

			Global_Handle(Mesh3d_Region) theRegion_;

			Global_Handle(Mesh_ReferenceValues) theReference_;

			Standard_Boolean IsDone_;

		public:

			Mesh3d_Ship();

			~Mesh3d_Ship();

			Global_Handle(M_CAD Compound_Ship) Ship() const;

			Global_Handle(Mesh3d_Region) Region() const;

			Global_Handle(Mesh_ReferenceValues) Reference() const;

			Standard_Boolean IsDone() const;

			void Init();

			void Perform();
		};
	}
}

#include <Mesh3d_ShipI.hxx>

#endif // !_Mesh3d_Ship_Header
