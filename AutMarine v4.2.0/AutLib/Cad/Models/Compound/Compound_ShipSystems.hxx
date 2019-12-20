#pragma once
#ifndef _Compound_ShipSystems_Header
#define _Compound_ShipSystems_Header

#include <gp_Ax2.hxx>
#include <Compound_ShipRudderSystemParameters.hxx>
#include <Compound_ShipPropellerSystemParameters.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Compound_ShipSystems
		{

		private:

			gp_Ax2 theHull_;
			gp_Ax2 theRudder_;
			gp_Ax2 theProp_;

		public:

			Compound_ShipSystems();

			void Init(const gp_Ax2& theHullSys, const gp_Ax2& theRudderSys, const gp_Ax2& thePropSys);

			const gp_Ax2& RudderSystem() const;

			const gp_Ax2& PropellerSystem() const;

			const gp_Ax2& HullSystem() const;

			void SetRudderSystem(const Compound_ShipRudderSystemParameters& theParameters);

			void SetPropellerSystem(const Compound_ShipPropellerSystemParameters& theParameters);
		};
	}
}

#include <Compound_ShipSystemsI.hxx>

#endif // !_Compound_ShipSystems_Header
