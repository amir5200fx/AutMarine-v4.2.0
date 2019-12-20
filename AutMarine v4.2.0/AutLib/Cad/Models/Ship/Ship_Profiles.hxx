#pragma once
#ifndef _Ship_Profiles_Header
#define _Ship_Profiles_Header

#include <TColShip_Ary1dOfShipParameterProfile.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Ship_Profiles
		{

		private:

			TColShip_Ary1dOfShipParameterProfile theFlare_;
			TColShip_Ary1dOfShipParameterProfile theSkeg_;
			TColShip_Ary1dOfShipParameterProfile theSection_;

			Ship_ShipParameterProfile theDeck_;
			Ship_ShipParameterProfile theButtock_;

		public:

			Ship_Profiles();

			void SetFlare(Standard_Integer Index, const Ship_ShipParameterProfile& Flare);

			void SetSkeg(Standard_Integer Index, const Ship_ShipParameterProfile& Skeg);

			void SetSection(Standard_Integer Index, const Ship_ShipParameterProfile& Section);

			void SetDeck(const Ship_ShipParameterProfile& Deck);

			void SetButtock(const Ship_ShipParameterProfile& Buttock);

			const Ship_ShipParameterProfile& Flare(Standard_Integer Index) const;

			const Ship_ShipParameterProfile& Skeg(Standard_Integer Index) const;

			const Ship_ShipParameterProfile& Section(Standard_Integer Index) const;

			const Ship_ShipParameterProfile& Deck() const;

			const Ship_ShipParameterProfile& Buttock() const;

			void SetMemory(const Standard_Integer nbSections);

			void ExportFlareToTecPlot(fstream& File) const;

			void ExportSkegToTecPlot(fstream& File) const;

			void ExportSectionToTecPlot(fstream& File) const;

			void ExportDeckToTecPlot(fstream& File) const;

			void ExportButtockToTecPlot(fstream& File) const;

		};
	}
}

#include <Ship_ProfilesI.hxx>

#endif // !_Ship_Profiles_Header
