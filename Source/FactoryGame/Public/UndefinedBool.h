// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

/** A bool that can be undefined */
UENUM()
enum class EUndefinedBool : uint8
{
	UB_Undefined,
	UB_False,
	UB_True
};

inline bool operator==( EUndefinedBool e, bool b );
inline bool operator==( bool b, EUndefinedBool e );
inline bool operator!=( EUndefinedBool e, bool b );
inline bool operator!=( bool b, EUndefinedBool e );
inline EUndefinedBool ToEnum( bool b );



bool operator==( EUndefinedBool e, bool b )
{
	if( b == true && e == EUndefinedBool::UB_True )
	{
		return true;
	}
	else if( b == false && e == EUndefinedBool::UB_False )
	{
		return true;
	}
	return false;
}

bool operator==( bool b, EUndefinedBool e )
{
	return e == b;
}

bool operator!=( EUndefinedBool e, bool b )
{
	bool result = !( e == b );

	return result;
}

bool operator!=( bool b, EUndefinedBool e )
{
	return !( e == b );
}

EUndefinedBool ToEnum( bool b )
{
	return b ? EUndefinedBool::UB_True : EUndefinedBool::UB_False;
}