#pragma once
#ifndef _FvSources2d_Methods_Header
#define _FvSources2d_Methods_Header

#include <FvSources2d_List.hxx>
#include <FvSources2d_Queue.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvSources2d_Methods
		{

		private:

			FvSources2d_Queue theMethods_;

		public:

			FvSources2d_Methods();

			void Insert(const Global_Handle(FvSources2d) theSource);

			void RetrieveTo(FvSources2d_List& theSources);
		};
	}
}

#endif // !_FvSources2d_Methods_Header
