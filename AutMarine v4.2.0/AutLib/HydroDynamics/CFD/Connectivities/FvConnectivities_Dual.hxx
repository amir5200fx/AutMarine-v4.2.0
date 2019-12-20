#pragma once
#ifndef _FvConnectivities_Dual_Header
#define _FvConnectivities_Dual_Header

#include <FvConnectivities.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvConnectivities_Dual : public FvConnectivities
		{

		private:

			Label theV0_;
			Label theV1_;

		public:

			FvConnectivities_Dual();

			Label Size() const;

			Label Value(const Label theIndex) const;

			void Import(fstream& File);
		};
	}
}

#include <FvConnectivities_DualI.hxx>

#endif // !_FvConnectivities_Dual_Header
