//#include <FvAssembly.hxx>
//
//#include <Global_Macros.hxx>
//#include <Global_Debug.hxx>
//#include <FvMatrix.hxx>
//
//using namespace AutLib;
//using namespace FvLib;
//
//AutLib::FvLib::FvAssembly::FvAssembly()
//	: theMatrix_(NULL)
//	, theSources_(NULL)
//{
//}
//
//Standard_Boolean AutLib::FvLib::FvAssembly::IsSameAs(const FvAssembly & theOther) const
//{
//	if (theMatrix_->Dim() NOT_EQUAL theOther.theMatrix_->Dim())
//	{
//		return Standard_False;
//	}
//
//	forThose
//	(
//		Index,
//		1, 
//		theMatrix_->Dim()
//	)
//	{
//		if (theMatrix_->BandSize(Index) NOT_EQUAL theOther.theMatrix_->BandSize(Index))
//		{
//			return Standard_False;
//		}
//
//		/*forThose
//		(
//			J,
//			1,
//			theMatrix_->BandSize(Index)
//		)
//		{
//			if (theMatrix_->GetPos(Index, J) NOT_EQUAL theOther.theMatrix_->GetPos(Index, J))
//			{
//				return Standard_False;
//			}
//		}*/
//	}
//	return Standard_True;
//}
//
//FvAssembly & AutLib::FvLib::FvAssembly::operator=(const FvAssembly & theOther)
//{
//	if (NOT IsSameAs(theOther)) { THROW_STANDARD_EXCEPTION("The two asseblies are not the same"); }
//
//	FvMatrix& Matrix = *theMatrix_;
//	const FvMatrix& Other = *theOther.Matrix();
//
//	forThose
//	(
//		Index,
//		1,
//		Matrix.Dim()
//	)
//	{
//		forThose
//		(
//			J,
//			1,
//			Matrix.BandSize(Index)
//		)
//		{
//			Matrix.SetValue(Index, J, Other.GetPos(Index, J), Other.GetValue(Index, J));
//		}
//	}
//
//	
//
//	return *this;
//}
//
//FvAssembly & AutLib::FvLib::FvAssembly::operator+=(const FvAssembly & theOther)
//{
//	if (NOT IsSameAs(theOther)) { THROW_STANDARD_EXCEPTION("The two asseblies are not the same"); }
//
//	FvMatrix& Matrix = *theMatrix_;
//	const FvMatrix& Other = *theOther.Matrix();
//
//	forThose
//	(
//		Index,
//		1,
//		Matrix.Dim()
//	)
//	{
//		forThose
//		(
//			J,
//			1,
//			Matrix.BandSize(Index)
//		)
//		{
//			Matrix.SetValue(Index, J, Other.GetPos(Index, J), (Scalar)0.0);
//			Matrix.AddValue(Index, J, Other.GetValue(Index, J));
//		}
//	}
//	return *this;
//}
//
//FvAssembly & AutLib::FvLib::FvAssembly::operator-=(const FvAssembly & theOther)
//{
//	if (NOT IsSameAs(theOther)) { THROW_STANDARD_EXCEPTION("The two asseblies are not the same"); }
//
//	FvMatrix& Matrix = *theMatrix_;
//	const FvMatrix& Other = *theOther.Matrix();
//
//	forThose
//	(
//		Index,
//		1,
//		Matrix.Dim()
//	)
//	{
//		forThose
//		(
//			J,
//			1,
//			Matrix.BandSize(Index)
//		)
//		{
//			Matrix.SetValue(Index, J, Other.GetPos(Index, J), (Scalar)0.0);
//			Matrix.AddValue(Index, J, -Other.GetValue(Index, J));
//		}
//	}
//	return *this;
//}
//
//FvAssembly & AutLib::FvLib::FvAssembly::operator+()
//{
//	return *this;
//}
//
//FvAssembly AutLib::FvLib::FvAssembly::operator-()
//{
//	return FvAssembly();
//}