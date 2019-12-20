#pragma once
#ifndef _Duct_Profiles_Header
#define _Duct_Profiles_Header

#include <TColDuct_Ary1dOfDuctParameterProfile.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Duct_Profiles
		{

		private:

			TColDuct_Ary1dOfDuctParameterProfile theSections_;

			Duct_DuctParameterProfile theBreadth_;
			Duct_DuctParameterProfile theDepth_;

		public:

			Duct_Profiles();

			void SetSection(const Standard_Integer theIndex, const Duct_DuctParameterProfile& theProfile);

			void SetBreadth(const Duct_DuctParameterProfile& theProfile);

			void SetDepth(const Duct_DuctParameterProfile& theProfile);

			const Duct_DuctParameterProfile& Section(const Standard_Integer theIndex);

			const Duct_DuctParameterProfile& Breadth() const;

			const Duct_DuctParameterProfile& Depth() const;

			void ExportSectionsToTecPlot(fstream& File) const;

			void SetMemory(const Standard_Integer nbSections);
		};
	}
}

#include <Duct_ProfilesI.hxx>

#endif // !_Duct_Profiles_Header
