#pragma once
#ifndef _Compound_Ship_Header
#define _Compound_Ship_Header

#include <Cad3d_MarineModel.hxx>
#include <Compound_ShipSystems.hxx>
#include <Compound_ShipRudderSystemParameters.hxx>
#include <Compound_ShipPropellerSystemParameters.hxx>
#include <Compound_ShipRudderSystemParametersBounds.hxx>
#include <Ship_Hull.hxx>
#include <Rudder.hxx>
#include <Prop_Propeller.hxx>

#include <TopoDS_Shape.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Compound_Ship : public Cad3d_MarineModel
		{

		private:

			Compound_ShipRudderSystemParametersBounds theRudderBounds_;

			Compound_ShipRudderSystemParameters theRudderParameters_;
			Compound_ShipPropellerSystemParameters thePropellerParameters_;

			Ship_Hull theShip_;

			Rudder theRudder_;

			Prop_Propeller thePropeller_;

			Compound_ShipSystems theSystems_;

		public:

			Compound_Ship();

			virtual ~Compound_Ship() {}

			virtual Global_Handle(Cad3d_Solid) GetSolid() const { return 0; }

			const Ship_Hull& Hull() const;

			const Rudder& Rudder() const;

			const Prop_Propeller& Propeller() const;

			void Make();

			void ExportToPlt(fstream& File) const;

		private:

			void DefaultParameters();

			void CalcSystems();

			void MakeSolid();
		};
	}
}

#include <Compound_ShipI.hxx>

#endif // !_Compound_Ship_Header
