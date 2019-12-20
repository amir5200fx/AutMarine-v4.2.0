#pragma once
template<typename T>
inline AutLib::NumLib::Numeric_AdptIntegral<T>::Numeric_AdptIntegral(const T * Object)
	: theObject_(Object)
	, theIntegrand_(0)
	, IsConverged_(Standard_False)
	, IsDone_(Standard_False)
	, theMaxIters_(50)
	, theUpper_(0)
	, theLower_(0)
	, theTolerance_(1.0E-10)
	, theInitialIter_(0)
{
}

template<typename T>
inline AutLib::NumLib::Numeric_AdptIntegral<T>::Numeric_AdptIntegral
(
	const T * Object,
	Standard_Real(*Integrand)(const Standard_Real, const T &)
)
	: theObject_(Object)
	, theIntegrand_(Integrand)
	, IsConverged_(Standard_False)
	, IsDone_(Standard_False)
	, theMaxIters_(50)
	, theUpper_(0)
	, theLower_(0)
	, theTolerance_(1.0E-10)
	, theInitialIter_(0)
{
}

template<typename T>
inline AutLib::NumLib::Numeric_AdptIntegral<T>::Numeric_AdptIntegral
(
	const T * Object, 
	Standard_Real(*Integrand)(const Standard_Real, const T &),
	const Standard_Real Lower,
	const Standard_Real Upper
)
	: theObject_(Object)
	, theIntegrand_(Integrand)
	, IsConverged_(Standard_False)
	, IsDone_(Standard_False)
	, theMaxIters_(50)
	, theUpper_(Upper)
	, theLower_(Lower)
	, theTolerance_(1.0E-10)
	, theInitialIter_(0)
{
}

template<typename T>
inline AutLib::NumLib::Numeric_AdptIntegral<T>::Numeric_AdptIntegral
(
	const T * Object, 
	Standard_Real(*Integrand)(const Standard_Real, const T &),
	const Standard_Real Lower,
	const Standard_Real Upper, 
	const Standard_Real Tolerance
)
	: theObject_(Object)
	, theIntegrand_(Integrand)
	, IsConverged_(Standard_False)
	, IsDone_(Standard_False)
	, theMaxIters_(50)
	, theUpper_(Upper)
	, theLower_(Lower)
	, theTolerance_(Tolerance)
	, theInitialIter_(0)
{
}

template<typename T>
inline void AutLib::NumLib::Numeric_AdptIntegral<T>::Perform()
{
	IsDone_ = Standard_True;

	Debug_Null_Pointer(theObject_);
	Debug_Null_Pointer(theIntegrand_);

	Debug_If_Condition(theLower_ == theUpper_);

	Standard_Real U0 = theLower_;
	Standard_Real U1 = theUpper_;

	TColStd_Ary1dOfReal 
		tol(theMaxIters_ + 10),
		a(theMaxIters_ + 10),
		h(theMaxIters_ + 10),
		FA(theMaxIters_ + 10),
		FC(theMaxIters_ + 10),
		FB(theMaxIters_ + 10),
		S(theMaxIters_ + 10);

	TColStd_Ary1dOfInteger L(theMaxIters_ + 10);

	Standard_Real APP = 0.;
	Standard_Integer i = 1;

	tol[i] = 10.0 * theTolerance_;
	a[i] = U0;
	h[i] = 0.5*(U1 - U0);

	Get_Const_Object(Object) = *theObject_;
	Get_Const_Object(Integrand) = *theIntegrand_;

	FA[i] = Integrand(U0, Object);
	FC[i] = Integrand(U0 + h[i], Object);
	FB[i] = Integrand(U1, Object);

	S[i] = h[i] * (FA[i] + 4.0*FC[i] + FB[i]) / 3.0;

	L[i] = 1;

	Standard_Real FD, FE, S1, S2;
	Standard_Real v1, v2, v3, v4, v5, v6, v7;
	Standard_Integer v8;
	Standard_Integer k = 0;

	Standard_Real C6 = 1.0 / 6.0;

	while (i > 0)
	{
		FD = Integrand(a[i] + 0.5*h[i], Object);
		FE = Integrand(a[i] + 1.5*h[i], Object);
		
		S1 = h[i] * (FA[i] + 4.0 * FD + FC[i]) * C6;
		S2 = h[i] * (FC[i] + 4.0 * FE + FB[i]) * C6;

		v1 = a[i];
		v2 = FA[i];
		v3 = FC[i];
		v4 = FB[i];
		v5 = h[i];
		v6 = tol[i];
		v7 = S[i];
		v8 = L[i];
		
		i--;

		k++;

		if (ABS(S1 + S2 - v7) < v6)
		{
			APP += (S1 + S2);
		}
		else
		{
			if (v8 >= theMaxIters_ + 1)
			{
				IsConverged_ = Standard_False;
				
				theResult_ = APP;

				return;
			}
			else
			{
				i++;

				a[i] = v1 + v5;
				FA[i] = v3;
				FC[i] = FE;
				FB[i] = v4;
				h[i] = 0.5*v5;
				tol[i] = MAX((Standard_Real)0.5 * v6, 1.0E-16);
				S[i] = S2;
				L[i] = v8 + 1;

				i++;

				a[i] = v1;
				FA[i] = v2;
				FC[i] = FD;
				FB[i] = v3;
				h[i] = h[i - 1];
				tol[i] = tol[i - 1];
				S[i] = S1;
				L[i] = L[i - 1];
			}
		}
	}

	theResult_ = APP;

	IsConverged_ = Standard_True;
}

template<typename T>
inline void AutLib::NumLib::Numeric_AdptIntegral<T>::SetIntegrand(Standard_Real(*Integrand)(const Standard_Real Parameter, const T &Object))
{
	theIntegrand_ = Integrand;
}

template<typename T>
inline void AutLib::NumLib::Numeric_AdptIntegral<T>::SetLower(const Standard_Real Value)
{
	theLower_ = Value;
}

template<typename T>
inline void AutLib::NumLib::Numeric_AdptIntegral<T>::SetUpper(const Standard_Real Value)
{
	theUpper_ = Value;
}

template<typename T>
inline void AutLib::NumLib::Numeric_AdptIntegral<T>::SetTolerance(const Standard_Real Value)
{
	theTolerance_ = Value;
}

template<typename T>
inline void AutLib::NumLib::Numeric_AdptIntegral<T>::SetMaxIteration(const Standard_Integer Iters)
{
	theMaxIters_ = Iters;
}

template<typename T>
inline void AutLib::NumLib::Numeric_AdptIntegral<T>::SetInitIter(const Standard_Integer Value)
{
	theInitialIter_ = Value;
}

template<typename T>
inline Standard_Boolean AutLib::NumLib::Numeric_AdptIntegral<T>::IsDone() const
{
	return IsDone_;
}

template<typename T>
inline Standard_Boolean AutLib::NumLib::Numeric_AdptIntegral<T>::IsConverged() const
{
	return IsConverged_;
}

template<typename T>
inline Standard_Real AutLib::NumLib::Numeric_AdptIntegral<T>::Result() const
{
	return theResult_;
}

template<typename T>
inline Standard_Integer AutLib::NumLib::Numeric_AdptIntegral<T>::MaxNbIterations() const
{
	return theMaxIters_;
}