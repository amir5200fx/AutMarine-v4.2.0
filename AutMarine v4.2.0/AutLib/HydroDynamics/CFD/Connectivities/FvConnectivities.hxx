#pragma once
#ifndef _FvConnectivities_Header
#define _FvConnectivities_Header

#include <FvPrimitives_Label.hxx>
#include <Standard_Stream.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvConnectivities
		{

		private:


		public:

			virtual Label Size() const = 0;

			virtual Label Value(const Label theIndex) const = 0;

			virtual void Import(fstream& File) = 0;

		};
	}
}

#endif // !_FvConnectivities_header
