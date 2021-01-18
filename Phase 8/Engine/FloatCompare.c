// Parent Header
#include "FloatCompare.h"



// Functions

// Public

bool Float64_ApproxEqual(float64 _first, float64 _second)
{
	//Implementation influenced by: https://floating-point-gui.de/errors/comparison/, https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/

	float64 firstAbs  = fabs(_first          ),
	        secondAbs = fabs(_second         ),
	        diffAbs   = fabs(_first - _second) ;

	bool ExactlyEqual,
		 CloseToZero  ;

	ExactlyEqual = (_first == _second                                     );
    CloseToZero  = (_first == 0       || _second == 0 || diffAbs < DBL_MIN);

	if (ExactlyEqual)       //Handles infinites
	{
		return true;
	}
	else if (CloseToZero)   //Close to zero
	{
		return (diffAbs < (DBL_EPSILON * DBL_EPSILON));
	}
	else                    //Relative Error
	{
		return (diffAbs / fmin(firstAbs + secondAbs, DBL_MAX) < DBL_EPSILON);
	}
}

bool Float64_ApproxGreater(float64 _first, float64 _second)
{
	//Implementation influenced by: https://floating-point-gui.de/errors/comparison/, https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/

	float64 firstAbs  = fabs(_first )      ,
		    secondAbs = fabs(_second)      ,
		    diff      = firstAbs - secondAbs ;

	bool ExactlyEqual,
		 CloseToZero  ;

	ExactlyEqual = (_first == _second                                        );
	CloseToZero  = (_first == 0       || _second == 0 || fabs(diff) < DBL_MIN);

	if (CloseToZero)   //Close to zero
	{
		return (diff > (DBL_EPSILON * DBL_MIN)) && !signbit(diff);
	}
	else               //Relative Error
	{
		return (diff / fmin(firstAbs + secondAbs, DBL_MAX) > DBL_EPSILON) && !signbit(diff);
	}
}

bool Float64_ApproxLess(float64 _first, float64 _second)
{
	//Implementation influenced by: https://floating-point-gui.de/errors/comparison/, https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/

	float64 firstAbs  = fabs(_first )        ,
	        secondAbs = fabs(_second)        ,
		    diff      = firstAbs - secondAbs   ;

	bool ExactlyEqual,
		 CloseToZero  ;

	ExactlyEqual = (_first == _second                                        );
	CloseToZero  = (_first == 0       || _second == 0 || fabs(diff) < DBL_MIN);

	if (CloseToZero)   //Close to zero
	{
		return (diff > (DBL_EPSILON * DBL_MIN)) && signbit(diff);
	}
	else               //Relative Error
	{
		return (diff / fmin(firstAbs + secondAbs, DBL_MIN) > DBL_EPSILON) && signbit(diff);
	}
}
