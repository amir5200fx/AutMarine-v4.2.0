#pragma once
#ifndef _FvConnectivities_General_Header
#define _FvConnectivities_General_Header

#include <FvConnectivities.hxx>
#include <FvList_Label.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvConnectivities_General : public FvConnectivities
		{

		private:

			FvList_Label theValues_;

		public:

			FvConnectivities_General();

			Label Size() const;

			Label Value(const Label theIndex) const;

			void Import(fstream& File);
		};
	}
}

#include <FvConnectivities_GeneralI.hxx>

#endif // !_FvConnectivities_General_Header
