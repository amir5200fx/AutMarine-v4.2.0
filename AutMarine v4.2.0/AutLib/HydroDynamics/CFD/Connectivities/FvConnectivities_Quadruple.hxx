#pragma once
#ifndef _FvConnectivities_Quadruple_Header
#define _FvConnectivities_Quadruple_Header

#include <FvConnectivities.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvConnectivities_Quadruple : public FvConnectivities
		{

		private:

			Label theV0_;
			Label theV1_;
			Label theV2_;
			Label theV3_;

		public:

			FvConnectivities_Quadruple();

			Label Size() const;

			Label Value(const Label theIndex) const;

			void Import(fstream& File);
		};
	}
}

#include <FvConnectivities_QuadrupleI.hxx>

#endif // !_FvConnectivities_Quadruple_Header
