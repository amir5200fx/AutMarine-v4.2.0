#pragma once
#ifndef _FvParameters_Precondition_Header
#define _FvParameters_Precondition_Header

namespace AutLib
{
	namespace FvLib
	{

		enum FvParameters_Precondition
		{

			FvParameters_Precondition_NONE = 0,
			FvParameters_Precondition_JACOBI,
			FvParameters_Precondition_SOR,
			FvParameters_Precondition_ILU,
			FvParameters_Precondition_ASM
		};
	}
}

#endif // !_FvParameters_Precondition_Header
