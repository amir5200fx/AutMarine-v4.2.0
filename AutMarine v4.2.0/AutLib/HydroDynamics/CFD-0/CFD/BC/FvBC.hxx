#pragma once
#ifndef _FvBC_Header
#define _FvBC_Header

#include <TColBC_HAry1dOfBoundary.hxx>
#include <TColBC_HBasicQueueOfBoundary.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvBC
		{

		private:

			TColBC_HBasicQueueOfBoundary theBoundaries_;

		public:

			FvBC();

			void InsertBoundary(const Global_Handle(FvBC_Boundary) theBoundary);

			void RetrieveTo(TColBC_HAry1dOfBoundary& theBoundaries);
		};
	}
}

#include <FvBCI.hxx>

#endif // !_FvBC_Header
