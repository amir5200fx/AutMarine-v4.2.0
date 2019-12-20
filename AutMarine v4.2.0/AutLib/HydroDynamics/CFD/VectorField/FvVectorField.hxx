#pragma once
#ifndef _FvVectorField_Header
#define _FvVectorField_Header

namespace AutLib
{
	namespace FvLib
	{

		class FvVectorField
		{

		private:


		public:

			virtual ~FvVectorField();

			/*virtual FvVectorField& operator=(const FvVectorField& theOther) = 0;

			virtual FvVectorField& operator+=(const FvVectorField& theOther) = 0;

			virtual FvVectorField& operator-=(const FvVectorField& theOther) = 0;

			virtual FvVectorField& operator+() = 0;

			virtual FvVectorField operator-() = 0;*/

		protected:

			FvVectorField();
		};
	}
}

#endif // !_FvVectorField_Header
