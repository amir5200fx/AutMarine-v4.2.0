#pragma once
#ifndef _FvConnectivities_Triple_Header
#define _FvConnectivities_Triple_Header

#include <FvConnectivities.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvConnectivities_Triple : public FvConnectivities
		{

		private:

			Label theV0_;
			Label theV1_;
			Label theV2_;

		public:

			FvConnectivities_Triple();

			Label Size() const;

			Label Value(const Label theIndex) const;

			void Import(fstream& File);
		};
	}
}

#include <FvConnectivities_TripleI.hxx>

#endif // !_FvConnectivities_Triple_Header
