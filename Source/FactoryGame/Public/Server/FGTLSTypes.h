// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

typedef struct ssl_st SSL;
typedef struct ssl_ctx_st SSL_CTX;
typedef struct x509_st X509;
typedef struct evp_pkey_st EVP_PKEY;
typedef struct bio_st BIO;

enum class EOSSLDataType
{
	None,
	SSLContext,
	SSL,
	X509,
	EVP_PKEY,
	BIO,
};

template<EOSSLDataType InDataType> struct TOSSLTypeOf;
template<> struct TOSSLTypeOf<EOSSLDataType::SSL> { using Value = SSL; };
template<> struct TOSSLTypeOf<EOSSLDataType::SSLContext> { using Value = SSL_CTX; };
template<> struct TOSSLTypeOf<EOSSLDataType::X509> { using Value = X509; };
template<> struct TOSSLTypeOf<EOSSLDataType::EVP_PKEY> { using Value = EVP_PKEY; };
template<> struct TOSSLTypeOf<EOSSLDataType::BIO> { using Value = BIO; };

enum EMoveIntoOSSLWrapperInternal { MoveIntoOSSLWrapper };

// A container for OpenSSL data types that automatically does reference counting
template<EOSSLDataType InDataType>
class TOSSLDataWrapper
{
public:
	using DataType = typename TOSSLTypeOf<InDataType>::Value*;
private:
	DataType DataInstance{};
public:
	TOSSLDataWrapper() = default;
	TOSSLDataWrapper( DataType InDataInstance );
	~TOSSLDataWrapper();
	TOSSLDataWrapper( EMoveIntoOSSLWrapperInternal, DataType InDataInstanceToMoveFrom );
	
	TOSSLDataWrapper( const TOSSLDataWrapper& InOther );
	TOSSLDataWrapper( TOSSLDataWrapper&& InOther ) noexcept;

	TOSSLDataWrapper& operator=( DataType InDataInstance );
	TOSSLDataWrapper& operator=( const TOSSLDataWrapper& InOther );
	TOSSLDataWrapper& operator=( TOSSLDataWrapper&& InOther ) noexcept;

	FORCEINLINE friend bool operator==( const TOSSLDataWrapper& A, const TOSSLDataWrapper& B )
	{
		return A.DataInstance == B.DataInstance;
	}

	FORCEINLINE friend bool operator!=( const TOSSLDataWrapper& A, const TOSSLDataWrapper& B )
	{
		return !(A == B);
	}
	
	FORCEINLINE DataType operator*() const { return DataInstance; }
	FORCEINLINE operator bool() const { return !!DataInstance; }
};

namespace OSSLDataWrapperSerializers
{
	FACTORYGAME_API void SerializePublicKey( FArchive& Ar, TOSSLDataWrapper<EOSSLDataType::EVP_PKEY>& PublicKey );
	FACTORYGAME_API void SerializePrivateKey( FArchive& Ar, TOSSLDataWrapper<EOSSLDataType::EVP_PKEY>& PrivateKey );
	FACTORYGAME_API void SerializeX509( FArchive& Ar, TOSSLDataWrapper<EOSSLDataType::X509>& Certificate );
}

namespace OSSLDataWrapperInternals
{
	FACTORYGAME_API void RefDownDataInstance( EOSSLDataType DataType, void* DataInstance );
	FACTORYGAME_API void RefUpDataInstance( EOSSLDataType DataType, void* DataInstance );
}

namespace OSSLUtilities
{
	/** Generates a fingerprint from the public key */
	FACTORYGAME_API FString FingerprintPublicKey( EVP_PKEY* PublicKey );
}

template<EOSSLDataType InDataType>
TOSSLDataWrapper<InDataType>::TOSSLDataWrapper( DataType InDataInstance ) : DataInstance( InDataInstance )
{
	if ( DataInstance )
	{
		OSSLDataWrapperInternals::RefUpDataInstance( InDataType, DataInstance );
	}
}

template<EOSSLDataType InDataType>
TOSSLDataWrapper<InDataType>::TOSSLDataWrapper( EMoveIntoOSSLWrapperInternal, DataType InDataInstanceToMoveFrom ) : DataInstance( InDataInstanceToMoveFrom )
{
}

template<EOSSLDataType InDataType>
TOSSLDataWrapper<InDataType>::~TOSSLDataWrapper()
{
	if ( DataInstance )
	{
		OSSLDataWrapperInternals::RefDownDataInstance( InDataType, DataInstance );
		DataInstance = nullptr;
	}
}

template<EOSSLDataType InDataType>
TOSSLDataWrapper<InDataType>::TOSSLDataWrapper( const TOSSLDataWrapper& InOther ) : TOSSLDataWrapper( *InOther )
{
}

template<EOSSLDataType InDataType>
TOSSLDataWrapper<InDataType>::TOSSLDataWrapper( TOSSLDataWrapper&& InOther ) noexcept : DataInstance( InOther.DataInstance )
{
	InOther.DataInstance = nullptr;
}

template<EOSSLDataType InDataType>
TOSSLDataWrapper<InDataType>& TOSSLDataWrapper<InDataType>::operator=( DataType InDataInstance )
{
	if ( DataInstance != InDataInstance )
	{
		if ( DataInstance )
		{
			OSSLDataWrapperInternals::RefDownDataInstance( InDataType, DataInstance );
			DataInstance = nullptr;
		}
		DataInstance = InDataInstance;
		if ( DataInstance )
		{
			OSSLDataWrapperInternals::RefUpDataInstance( InDataType, DataInstance );
		}
	}
	return *this;
}

template<EOSSLDataType InDataType>
TOSSLDataWrapper<InDataType>& TOSSLDataWrapper<InDataType>::operator=( const TOSSLDataWrapper& InOther )
{
	return operator=( *InOther );
}

template<EOSSLDataType InDataType>
TOSSLDataWrapper<InDataType>& TOSSLDataWrapper<InDataType>::operator=( TOSSLDataWrapper&& InOther ) noexcept
{
	if ( DataInstance != InOther.DataInstance )
	{
		if ( DataInstance )
		{
			OSSLDataWrapperInternals::RefDownDataInstance( InDataType, DataInstance );
			DataInstance = nullptr;
		}
		DataInstance = InOther.DataInstance;
		InOther.DataInstance = nullptr;
	}
	return *this;
}

