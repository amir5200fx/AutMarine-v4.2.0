#pragma once
template<typename T>
inline AutLib::NumLib::Numeric_NewtonIter<T>::Numeric_NewtonIter
(
	const T * Object, 
	const Standard_Real Tolerance
)
	: theObject_(Object)
	, theValueFunction_(0)
	, theDeriveFunction_(0)
	, theMaxIterations_(500)
	, theIter_(0)
	, theTolerance_(Tolerance)
	, theSmall_(1.0E-6)
	, theResidual_(0)
	, IsDone_(Standard_False)
	, theUnderRelaxation_(0.9)
{
}

template<typename T>
inline AutLib::NumLib::Numeric_NewtonIter<T>::Numeric_NewtonIter
(
	const T * Object,
	Standard_Real(*Function)(const Standard_Real, const T &), 
	Standard_Real(*Derive)(const Standard_Real, const T &),
	const Standard_Real Tolerance
)
	: theObject_(Object)
	, theValueFunction_(Function)
	, theDeriveFunction_(Derive)
	, theMaxIterations_(500)
	, theIter_(0)
	, theTolerance_(Tolerance)
	, theSmall_(1.0E-6)
	, theResidual_(0)
	, IsDone_(Standard_False)
	, theUnderRelaxation_(0.9)
{
}

template<typename T>
inline void AutLib::NumLib::Numeric_NewtonIter<T>::SetIterations(const Standard_Integer nbIterations)
{
	theMaxIterations_ = nbIterations;
}

template<typename T>
inline void AutLib::NumLib::Numeric_NewtonIter<T>::SetTolerance(const Standard_Real Tolerance)
{
	theTolerance_ = Tolerance;
}

template<typename T>
inline void AutLib::NumLib::Numeric_NewtonIter<T>::SetSmall(const Standard_Real Small)
{
	theSmall_ = Small;
}

template<typename T>
inline void AutLib::NumLib::Numeric_NewtonIter<T>::SetUnderRelaxation(const Standard_Real UnderRelaxation)
{
	theUnderRelaxation_ = UnderRelaxation;
}

template<typename T>
inline void AutLib::NumLib::Numeric_NewtonIter<T>::SetZero(const Standard_Real Zero)
{
	theZero_ = Zero;
}

template<typename T>
inline void AutLib::NumLib::Numeric_NewtonIter<T>::Iterate(const Standard_Real guess)
{
	IsDone_ = Standard_True;

	Debug_Null_Pointer(theValueFunction_);
	Debug_Null_Pointer(theDeriveFunction_);

	Debug_Null_Pointer(theObject_);

	Get_Const_Object(Object) = *theObject_;

	Standard_Real y0;

	Try_Exception_Handle_Exit(y0 = theValueFunction_(guess, Object));

	Standard_Real df, dp, p1, y1, rel_err, u;

	theCondition_ = NewtonIter_LEVEL_EXCEEDED;

	u = guess;

	theIter_ = 0;

	forThose(Iter, 1, theMaxIterations_)
	{
		theIter_++;

		Try_Exception_Handle_Exit(df = theDeriveFunction_(u, Object));

		if (ABS(df) == 0.)
		{
			theCondition_ = NewtonIter_ZERODIVIDE;
			dp = 0;
		}
		else
			dp = y0 / df;

		p1 = u - theUnderRelaxation_*dp;

		Try_Exception_Handle_Exit(y1 = theValueFunction_(p1, Object));

		rel_err = 2.0 * ABS(dp) / (ABS(p1) + theSmall_);

		if (rel_err < theTolerance_ OR ABS(y1) < theZero_)
			if (theCondition_ NOT_EQUAL NewtonIter_ZERODIVIDE) theCondition_ = NewtonIter_CONVERGED;

		u = p1;
		y0 = y1;

		if ((Standard_Integer)theCondition_)
			break;
	}

	theResult_ = u;
	theResidual_ = rel_err;
}

template<typename T>
inline M_NUMER NewtonIterCondition AutLib::NumLib::Numeric_NewtonIter<T>::Condition() const
{
	return theCondition_;
}

template<typename T>
inline Standard_Real AutLib::NumLib::Numeric_NewtonIter<T>::Result() const
{
	return theResult_;
}

template<typename T>
inline Standard_Real AutLib::NumLib::Numeric_NewtonIter<T>::Residual() const
{
	return theResidual_;
}

template<typename T>
inline Standard_Integer AutLib::NumLib::Numeric_NewtonIter<T>::NbIterated() const
{
	return theIter_;
}

template<typename T>
inline Standard_Boolean AutLib::NumLib::Numeric_NewtonIter<T>::IsDone() const
{
	return IsDone_;
}