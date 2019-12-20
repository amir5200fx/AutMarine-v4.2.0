#include <FvMatrix_Laspack.hxx>

#include <Global_Macros.hxx>

AutLib::FvLib::FvMatrix_Laspack::FvMatrix_Laspack()
{
}

Standard_Boolean AutLib::FvLib::FvMatrix_Laspack::IsSameAs(const FvMatrix & theOther) const
{
	if (Dim() NOT_EQUAL theOther.Dim())
	{
		return Standard_False;
	}

	forThose(Index, 1, Dim())
	{
		if (BandSize(Index) NOT_EQUAL theOther.BandSize(Index))
		{
			return Standard_False;
		}

		forThose(J, 1, BandSize(Index))
		{
			if (GetPos(Index, J) NOT_EQUAL theOther.GetPos(Index, J))
			{
				return Standard_False;
			}
		}
	}
	return Standard_True;
}

void AutLib::FvLib::FvMatrix_Laspack::AllocateDim
(
	const Label theSize, 
	const Standard_Boolean Symmetry
)
{
	Q_Constr((QMatrix*)&theMatrix_, (char*)FvMatrix::Name().c_str(), (size_t)theSize, (Symmetry == Standard_True) ? True : False, ElOrderType::Rowws, InstanceType::Normal, True);
}

void AutLib::FvLib::FvMatrix_Laspack::ReleaseMemory()
{
	Q_Destr((QMatrix*)&theMatrix_);
}