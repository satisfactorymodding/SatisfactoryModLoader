#pragma once

#include "CoreMinimal.h"
#include "Serialization/MemoryReader.h"
#include "Containers/Queue.h"
#include "Serialization/MemoryWriter.h"
#include "BulkDataReplicationModule.h"

enum class EReliableDataProtocolOpCode : uint8
{
	Invalid,
	/**
	 * A GUID is sent through both the UNetConnection and the BulkDataReplicationConnectionHandler
	 * and the server then uses this GUID to map the connection BulkDataReplicationConnectionHandler to a player controller component.
	 * We cannot rely on address as multiple clients can connect from the same address.
	 **/
	Handshake,
	/**
	 * The initial message chunk is exactly what its name suggests. In addition to being like any other chunk, it also contains the total size of the message.
	 * We have a separate type for it to avoid sending the total size with every chunk. If the entire message fits in one chunk, this will also be the last chunk.
	 */
	MessageHeader,
	/**
	 * A message chunk that is not the first. It might be the last though.
	 */
	ChunkHeader,
	/**
	 * A message chunk acknowledgment. This is sent by the client to the server to acknowledge that it has received a chunk.
	 * NumChunks: 4 bytes the number of chunks we have acknowledged.
	 * 8 bytes * NumChunks: The message ids that we acknowledge for.
	 * 4 bytes * NumChunks: The chunk indexes that we acknowledge for. One for every message id. The assumption is that if chunk n is acknowledged, all chunks before it are also acknowledged. We can make that assumption since we are using a reliable transport layer.
	 */
	Ack
};

namespace RDTProtocol
{
	/** The size type used by the protocol. This will show up in all the various headers the protocol throws around. */
	using SizeType = TArray<uint8>::SizeType;
	/** The message id type used by the protocol. @todo: Consider changing the semantics of this id to allow overflowing. We could get away with a smaller type. */
	using MessageIdType = uint64;

	/**
	 * This is the structure that the protocol sends describing a message, before the message data itself.
	 */
	struct RELIABLEMESSAGING_API FMessageHeader
	{
		static constexpr uint32 SerializedSize = sizeof(MessageIdType) + sizeof(uint8) + sizeof(SizeType);
		/** A message id used to internally track messages. */
		MessageIdType MessageId;
		/** The channel id that this message is associated with. */
		uint8 ChannelId;
		/** The *TOTAL* length of the message. */
		SizeType Length;
	};

	struct RELIABLEMESSAGING_API FMessage
	{
		FMessage() = default;
		explicit FMessage(const FMessageHeader& InHeader)
			: MessageId(InHeader.MessageId)
			, ChannelId(InHeader.ChannelId)
		{
			Data.SetNumUninitialized(InHeader.Length);
		}

		FMessage(const uint64 InMessageId, const uint8 InChannelId, TArray<uint8>&& InData)
			: MessageId(InMessageId)
			, ChannelId(InChannelId)
			, Data(MoveTemp(InData))
		{
		}

		FMessage(const FMessage&) = delete;
		FMessage(FMessage&&) = default;

		FMessage& operator=(const FMessage&) = delete;
		FMessage& operator=(FMessage&&) = default;

		MessageIdType MessageId = std::numeric_limits<MessageIdType>::max();
		uint8 ChannelId = std::numeric_limits<uint8>::max();
		TArray<uint8> Data;
	};

	struct RELIABLEMESSAGING_API FChunkHeader
	{
		static constexpr uint32 SerializedSize = sizeof(MessageIdType) + sizeof(uint8) + sizeof(SizeType);
		/* Same as the message id from the message header */
		MessageIdType MessageId;
		/* Same as above */
		uint8 ChannelId;
		/* The length of this chunk. */
		SizeType Length;
	};
} // namespace RDTProtocol

inline FArchive& operator<<(FArchive& Ar, RDTProtocol::FMessageHeader& Header)
{
	Ar << Header.MessageId;
	Ar << Header.ChannelId;
	Ar << Header.Length;
	return Ar;
}

inline FArchive& operator<<(FArchive& Ar, RDTProtocol::FChunkHeader& Header)
{
	Ar << Header.MessageId;
	Ar << Header.ChannelId;
	Ar << Header.Length;
	return Ar;
}

/**
 * The writer component of our protocol. It is responsible for writing messages in a transport agnostic way and also keep track of the progress of the messages
 * derived from the acknowledgments sent by the remote party.
 */
template <typename Base>
class FReliableDataTransferProtocolWriter
{
public:
	using BaseType = Base;
	explicit FReliableDataTransferProtocolWriter(RDTProtocol::SizeType InMaxPacketSize);

	void WriteCycle()
	{
		// @todo: Shouldn't happen here, should be driven by the protocol reader when it receives an acknowledgment.
		// for (auto& [Priority, FinishedMessaged] : FullyDispatchedMessages)
		// {
		// 	for (FPendingMessage* FinishedMessage : FinishedMessaged)
		// 	{
		// 		FullyDispatchedMessages[Priority].Remove(FinishedMessage);
		// 	}
		// }

		// Then dispatch any pending messages, in order of priority, until the socket is full.
		bool bCanStillSend = true;
		while (bCanStillSend && !PendingMessages.IsEmpty())
		{
			FOutboundMessage& PendingMessage = *PendingMessages.Peek();
			if (PendingMessage.MessageBytesSent == PendingMessage.Data.Num())
			{
				FullySentMessages.Add(MoveTemp(PendingMessage));
				PendingMessages.Pop();
			}
			else if (PendingMessage.MessageBytesSent < PendingMessage.Data.Num())
			{
				if (!PendingMessage.bHasSentHeader)
				{
					// If we're at the start of the message and haven't sent a single byte of the header yet,
					// it means we first have to serialize the header
					if (PendingMessage.HeaderBytesSent == 0)
					{
						RDTProtocol::FMessageHeader Header;
						Header.MessageId = PendingMessage.MessageId;
						Header.ChannelId = PendingMessage.ChannelId;
						Header.Length = PendingMessage.Data.Num();

						WriteBuffer.SetNumUninitialized(0, false);
						FMemoryWriter HeaderWriter(WriteBuffer);
						EReliableDataProtocolOpCode HeaderType = EReliableDataProtocolOpCode::MessageHeader;
						HeaderWriter << HeaderType;
						HeaderWriter << Header;
					}

					RDTProtocol::SizeType BytesWritten = 0;
					if (static_cast<BaseType&>(*this).WriteData(WriteBuffer.GetData() + PendingMessage.HeaderBytesSent,
						WriteBuffer.Num() - PendingMessage.HeaderBytesSent, BytesWritten))
					{
						PendingMessage.HeaderBytesSent += BytesWritten;
						bCanStillSend = BytesWritten == WriteBuffer.Num();
						if (PendingMessage.HeaderBytesSent == WriteBuffer.Num())
						{
							PendingMessage.bHasSentHeader = true;
						}
					}
					else
					{
						// If we couldn't send this packet, stop iterating altogether. We'll try again next tick.
						bCanStillSend = false;
					}
				}

				// Send out as many chunks as the socket can handle.
				while (PendingMessage.MessageBytesSent < PendingMessage.Data.Num() && bCanStillSend)
				{
					if (PendingMessage.ChunkBytesSent == 0)
					{
						// We need to send a new chunk header)
						RDTProtocol::FChunkHeader ChunkHeader;
						ChunkHeader.MessageId = PendingMessage.MessageId;
						PendingMessage.CurrentChunkSize = FMath::Min(
							static_cast<int32>(MaxPacketSize - (1 + RDTProtocol::FChunkHeader::SerializedSize)),
							PendingMessage.Data.Num() - PendingMessage.MessageBytesSent);
						ChunkHeader.Length = PendingMessage.CurrentChunkSize;
						ChunkHeader.ChannelId = PendingMessage.ChannelId;

						WriteBuffer.SetNumUninitialized(0, false);
						FMemoryWriter ChunkDataWriter(WriteBuffer);
						EReliableDataProtocolOpCode ChunkType = EReliableDataProtocolOpCode::ChunkHeader;
						ChunkDataWriter << ChunkType;
						ChunkDataWriter << ChunkHeader;
						ChunkDataWriter.Serialize(PendingMessage.Data.GetData() + PendingMessage.MessageBytesSent, PendingMessage.CurrentChunkSize);
					}

					RDTProtocol::SizeType BytesWritten = 0;

					if (static_cast<BaseType&>(*this).WriteData(WriteBuffer.GetData() + PendingMessage.ChunkBytesSent, WriteBuffer.Num() - PendingMessage.ChunkBytesSent, BytesWritten))
					{
						PendingMessage.ChunkBytesSent += BytesWritten;
						if (PendingMessage.ChunkBytesSent == WriteBuffer.Num())
						{
							PendingMessage.MessageBytesSent += PendingMessage.CurrentChunkSize;
							PendingMessage.ChunkBytesSent = 0;
							bCanStillSend = true;
						}
						else
						{
							// We just filled the socket, shut the pipe
							bCanStillSend = false; 
						}
					}
					else
					{
						// If we couldn't send this packet, stop iterating altogether. We'll try again next tick.
						bCanStillSend = false;
					}
				}
			}
		}
	}

	bool SendConnectionId(FGuid ConnectionId)
	{
		WriteBuffer.SetNumUninitialized(0, false);
		FMemoryWriter Writer(WriteBuffer);
		uint8 HeaderType = static_cast<uint8>(EReliableDataProtocolOpCode::Handshake);
		
		Writer << HeaderType;
		Writer << ConnectionId;
		
		check(WriteBuffer.Num() == 1 + sizeof(FGuid));

		RDTProtocol::SizeType BytesWritten = 0;
		bool bSendResult = static_cast<BaseType&>(*this).WriteData(WriteBuffer.GetData(), WriteBuffer.Num(), BytesWritten);
		return bSendResult && BytesWritten == WriteBuffer.Num();
	}

	void EnqueueMessage(uint8 ChannelId, TArray<uint8>&& Data, bool bSendImmediately = false)
	{
		PendingMessages.Enqueue(FOutboundMessage(NextMessageId++, ChannelId, MoveTemp(Data)));
		if (bSendImmediately)
		{
			WriteCycle();
		}
	}

	bool HasOutboundMessages() const
	{
		return !PendingMessages.IsEmpty();
	}

private:
	
	struct FOutboundMessage: RDTProtocol::FMessage
	{
		using FMessage::FMessage;

		FOutboundMessage() = default;
		FOutboundMessage(const FOutboundMessage&) = delete;
		FOutboundMessage(FOutboundMessage&&) = default;

		FOutboundMessage& operator=(const FOutboundMessage&) = delete;
		FOutboundMessage& operator=(FOutboundMessage&&) = default;

		/**
		 * The position of the last confirmed byte in the message. This is used to keep track of the progress of the message.
		 */
		RDTProtocol::SizeType LastConfirmedPosition = 0;
		/**
		 * How many bytes of the message have been sent up to this point. This is used to keep track of the progress of the message.
		 */
		RDTProtocol::SizeType MessageBytesSent = 0;
		/**
		* Track whether we have sent the header for this message. We need to send the header before we can send the message data.
		*/
		bool bHasSentHeader = false;
		/**
		 *
		 */
		RDTProtocol::SizeType ChunkBytesSent = 0;
		/**
		 *
		 */
		RDTProtocol::SizeType HeaderBytesSent = 0;
		/**
		 *
		 */
		RDTProtocol::SizeType CurrentChunkSize = 0;
	};
	
	/**
	 * All the messages that are pending to be sent. They are not sorted in any way, it's a purely FIFO queue.
	 */
	TQueue<FOutboundMessage> PendingMessages;
	
	/**
	 * The messages that we have fully sent but have not been fully acknowledged by the remote host.
	 * We keep them around in case we need to resend them on a reconnect.
	 */
	TArray<FOutboundMessage> FullySentMessages;
	
	const RDTProtocol::SizeType MaxPacketSize = 0;
	TArray<uint8> WriteBuffer;

	RDTProtocol::MessageIdType NextMessageId = 0;
};

/**
 * This is a stream based protocol, which means we need to build a parser that can break the stream into messages.
 * The protocol also maintains the read buffer for the socket. This is necessary since the parser may not be able to fully consume the data
 * from one read, and it needs to be able to continue parsing from where it left off.
 */
template <typename Base>
class FReliableDataTransferProtocolReader
{
public:
	using BaseType = Base;
	
	explicit FReliableDataTransferProtocolReader(RDTProtocol::SizeType ReadBufferLength);
	FReliableDataTransferProtocolReader(const FReliableDataTransferProtocolReader&) = delete;
	FReliableDataTransferProtocolReader(FReliableDataTransferProtocolReader&&) = default;

	FReliableDataTransferProtocolReader& operator=(const FReliableDataTransferProtocolReader&) = delete;
	FReliableDataTransferProtocolReader& operator=(FReliableDataTransferProtocolReader&&) = delete;
	
	void ReadCycle();
private:
	/**
	 * Parse all the data in the read buffer. This function should be called after every read from the socket.
	 */
	void ParsePacket();

	/**
	 * Returns a writeable buffer that can be used to write the next message. Sockets should read into this buffer and this function should be called before
	 * every recv
	 * @return 
	 */
	TArrayView<uint8> GetParseBuffer();
	

	void ParseHeaderType(FArchive& Ar);
	void ParseConnectionId(FArchive& Ar);
	void ParseMessageHeader(FArchive& Ar);
	void ParseChunk(FArchive& Ar);
	
	struct FInboundMessage: RDTProtocol::FMessage
	{
		FInboundMessage(const RDTProtocol::FMessageHeader& InHeader)
			: FMessage(InHeader)
		{
		}

		FInboundMessage(const FInboundMessage&) = delete;
		FInboundMessage(FInboundMessage&&) = default;

		FInboundMessage& operator=(const FInboundMessage&) = delete;
		FInboundMessage& operator=(FInboundMessage&&) = default;

		bool IsComplete() const
		{
			return Offset == Data.Num();
		}

		RDTProtocol::SizeType GetRemainingBytes() const
		{
			return Data.Num() - Offset;
		}
		
		RDTProtocol::SizeType Offset = 0;
	};

	struct FChannelData
	{
		/** Messages that are currently being parsed are stored here until they are fully */
		TArray<FInboundMessage> PendingMessages;
	};
	
	struct FPendingChunk: RDTProtocol::FChunkHeader
	{
		FPendingChunk() = default;
		explicit FPendingChunk(const RDTProtocol::FChunkHeader& InChunk)
			: FChunkHeader(InChunk)
		{
		}

		FPendingChunk(const FPendingChunk&) = delete;
		FPendingChunk(FPendingChunk&&) = default;

		FPendingChunk& operator=(const FPendingChunk&) = delete;
		FPendingChunk& operator=(FPendingChunk&&) = default;
		
		RDTProtocol::SizeType Offset = 0;
		FInboundMessage* PendingMessagePtr = nullptr;
	};

	enum class EParserState: uint8
	{
		ParsingHeaderType,
		ParsingConnectionId,
		WaitingForChannelId,
		WaitingForTaggedPayloadLength,
		WaitingForTaggedPayloadData,
		ParsingMessageHeader,
		ParsingChunk,
		Error
	};

	TArray<FChannelData> PerChannelData = {};
	TOptional<FPendingChunk> PendingChunk = {};

	EParserState ParserState = EParserState::ParsingHeaderType;
	
	TArray<uint8> ReadBuffer;
	RDTProtocol::SizeType ReadBufferOffset = 0;
	const RDTProtocol::SizeType ReadBufferLength = 0;

	void SwitchState(EParserState NewState);
};

template <typename Base>
void FReliableDataTransferProtocolReader<Base>::ReadCycle()
{
	// First read all available packets from the socket.
	int32 BytesRead = 0;
	while(static_cast<BaseType&>(*this).ReadData(GetParseBuffer().GetData(), GetParseBuffer().Num(), BytesRead) && BytesRead > 0)
	{
		// Resize the buffer to the actual size of the data within
		ReadBuffer.SetNum(ReadBufferOffset + BytesRead, false);

		ParsePacket();
	}
}

template <typename Base>
FReliableDataTransferProtocolWriter<Base>::FReliableDataTransferProtocolWriter(RDTProtocol::SizeType InMaxPacketSize)
	: MaxPacketSize(InMaxPacketSize)
{
	WriteBuffer.SetNumUninitialized(MaxPacketSize);
}

template <typename Base>
FReliableDataTransferProtocolReader<Base>::FReliableDataTransferProtocolReader(RDTProtocol::SizeType ReadBufferLength)
	: ReadBufferLength(ReadBufferLength)
{
	ReadBuffer.SetNumUninitialized(ReadBufferLength);
}

template<typename Base>
void FReliableDataTransferProtocolReader<Base>::ParsePacket()
{
	FMemoryReader MemoryReader(ReadBuffer);
	
	// Parse as long as we can
	while (!MemoryReader.AtEnd() && !MemoryReader.GetError())
	{
		switch (ParserState)
		{
			case EParserState::ParsingHeaderType:
				ParseHeaderType(MemoryReader);
				break;
			case EParserState::ParsingMessageHeader:
				ParseMessageHeader(MemoryReader);
				break;
			case EParserState::ParsingChunk:
				ParseChunk(MemoryReader);
				break;
			case EParserState::ParsingConnectionId:
				ParseConnectionId(MemoryReader);
				break;
			default:
			{
				// Set the error flag so we can stop trying to parse any data this tick
				MemoryReader.SetError();
				UE_LOG(LogReliableMessaging, Error, TEXT("Received an invalid message type. Disconnecting."));
				// No way to recover from here. Let the transport layer know that we're disconnecting so they can deal with it.
				static_cast<BaseType&>(*this).CloseConnection();
			}
			break;
		}
	}

	// If there's an error, it must be because there was insufficient data to read the next element, so we need to preserve the part of the
	// buffer that we haven't read yet.
	if (MemoryReader.GetError())
	{
		RDTProtocol::SizeType UnreadBytesOffset = MemoryReader.Tell();
		// First move the unread bytes to the beginning of the buffer
		ReadBuffer.RemoveAt(0, UnreadBytesOffset, false);
		// And record the position so we don't overwrite these bytes until we've processed them
		ReadBufferOffset = ReadBuffer.Num();
		// Ultimately make sure the read buffer has enough room for next read
		ReadBuffer.SetNumUninitialized(ReadBufferOffset + ReadBufferLength, false);
	}
	else
	{
		// We've read all the data in the buffer, so we can reset the buffer offset. We can let the read buffer keep it's size. 
		ReadBufferOffset = 0;
		ReadBuffer.SetNumUninitialized(ReadBufferLength, false);
	}
}

template <typename Base>
TArrayView<uint8> FReliableDataTransferProtocolReader<Base>::GetParseBuffer()
{
	return TArrayView<uint8>(ReadBuffer.GetData() + ReadBufferOffset, ReadBuffer.Num() - ReadBufferOffset);
}

template <typename Base>
void FReliableDataTransferProtocolReader<Base>::ParseHeaderType(FArchive& Ar)
{
	EReliableDataProtocolOpCode MessageType;
	Ar << reinterpret_cast<uint8&>(MessageType);

	// We should never get an error here, because we're only reading a single byte
	check(!Ar.GetError());

	// We have a message type, so we can switch to the next state
	EParserState NewState = EParserState::Error;
	switch (MessageType)
	{
		case EReliableDataProtocolOpCode::Handshake:
			NewState = EParserState::ParsingConnectionId;
			break;
		case EReliableDataProtocolOpCode::MessageHeader:
			// We need to read the message header next
			NewState = EParserState::ParsingMessageHeader;
			break;
		case EReliableDataProtocolOpCode::ChunkHeader:
			// We need to read the chunk header next
			NewState = EParserState::ParsingChunk;
			break;
		default:
			// We've received an invalid message type, so we need to reset the state machine. Means we must have a bug in the protocol or parser.
			// This is already handled in ParsePacket as long as the NewState is set to Error.
			break;
	}

	SwitchState(NewState);
}

template <typename Base>
void FReliableDataTransferProtocolReader<Base>::ParseConnectionId(FArchive& Ar)
{
	static_assert(sizeof(FGuid) == 4 * sizeof(uint32), "This assumes an FGuid is 4 * uint32. If FGuid changes then this must change too.");
	if (Ar.Tell() + static_cast<int64>(sizeof(FGuid)) <= Ar.TotalSize())
	{
		// We can proceed with reading the guid
		FGuid ConnectionId;
		Ar << ConnectionId;

		static_cast<BaseType&>(*this).HandleConnectionIdReceived(ConnectionId);
		
		// We're done with this message, reset the state machine
		SwitchState(EParserState::ParsingHeaderType);
	}
	else
	{
		Ar.SetError();
	}
}

template <typename Base>
void FReliableDataTransferProtocolReader<Base>::ParseMessageHeader(FArchive& Ar)
{
	if (Ar.Tell() + RDTProtocol::FMessageHeader::SerializedSize <= Ar.TotalSize())
	{
		RDTProtocol::FMessageHeader MessageHeader;
		Ar << MessageHeader;
		check(!Ar.IsError());
		
		if (PerChannelData.Num() < MessageHeader.ChannelId + 1)
		{
			PerChannelData.SetNum(MessageHeader.ChannelId + 1);
		}

		if (PerChannelData[MessageHeader.ChannelId].PendingMessages.FindByPredicate(
			[&MessageHeader](const FInboundMessage& PendingMessage)
		{
			return PendingMessage.MessageId == MessageHeader.MessageId;
		}) != nullptr)
		{
			Ar.SetError();
			UE_LOG(LogReliableMessaging, Error,
				TEXT("Received a message with a duplicate message id. Closing connection."));
			static_cast<BaseType&>(*this).CloseConnection();
			return;
		}
		
		PerChannelData[MessageHeader.ChannelId].PendingMessages.Emplace(MoveTemp(MessageHeader));
		SwitchState(EParserState::ParsingHeaderType);
	}
	else
	{
		Ar.SetError();
	}
}

template <typename Base>
void FReliableDataTransferProtocolReader<Base>::ParseChunk(FArchive& Ar)
{
	// Try to read the chunk header atomically first.
	if (!PendingChunk.IsSet())
	{
		if (Ar.Tell() + RDTProtocol::FChunkHeader::SerializedSize <= Ar.TotalSize())
		{
			RDTProtocol::FChunkHeader ChunkHeader;
			Ar << ChunkHeader;
			check(!Ar.IsError());

			// Make sure this chunk was expected at this time. 
			if (!PerChannelData.IsValidIndex(ChunkHeader.ChannelId))
			{
				// Semantic error, if the channel id is invalid, this chunk header wasn't preceded by a message header.
				Ar.SetError();
				UE_LOG(LogReliableMessaging, Error,
					TEXT("Chunk header refers to an invalid channel id. A message header wasn't sent before this chunk. Closing connection."));
				static_cast<BaseType&>(*this).CloseConnection();
				return;
			}

			PendingChunk.Emplace(ChunkHeader);
			PendingChunk->PendingMessagePtr = PerChannelData[PendingChunk->ChannelId].PendingMessages.FindByPredicate(
				[this](const FInboundMessage& PendingMessage)
			{
				return PendingMessage.MessageId == PendingChunk->MessageId;
			});

			if (PendingChunk->PendingMessagePtr == nullptr)
			{
				Ar.SetError();
				UE_LOG(LogReliableMessaging, Error,
					TEXT("Chunk header refers to an invalid message id. A message header wasn't sent before this chunk. Closing connection."));
				static_cast<BaseType&>(*this).CloseConnection();
				return;
			}
		}
		else
		{
			// We don't have enough data to read the chunk header, so we can't proceed. Let us try again once we've acquired more data.
			Ar.SetError();
			return;
		}
	}

	{
		// Make sure the length of this chunk does not exceed the length of the message. This would be an unrecoverable error. 
		if ((PendingChunk->Length - PendingChunk->Offset) > PendingChunk->PendingMessagePtr->GetRemainingBytes())
		{
			Ar.SetError();
			UE_LOG(LogReliableMessaging, Error, TEXT("Chunk length is greater than remaining message length. Closing connection."));
			static_cast<BaseType&>(*this).CloseConnection();
			return;
		}
		const RDTProtocol::SizeType ReadLen = FMath::Min(PendingChunk->Length - PendingChunk->Offset, Ar.TotalSize() - Ar.Tell());
		uint8* ReadPosition = PendingChunk->PendingMessagePtr->Data.GetData() + PendingChunk->PendingMessagePtr->Offset;
		Ar.Serialize(ReadPosition, ReadLen);
		check(!Ar.IsError());

		PendingChunk->PendingMessagePtr->Offset += ReadLen;
		PendingChunk->Offset += ReadLen;

		if (PendingChunk->Offset == PendingChunk->Length)
		{
			if (PendingChunk->PendingMessagePtr->Data.Num() == PendingChunk->PendingMessagePtr->Offset)
            {
            	// This message is now fully read, so we can move it to the fully read messages array
				RDTProtocol::FMessage FullyReadMessage = MoveTemp(static_cast<RDTProtocol::FMessage&>(*PendingChunk->PendingMessagePtr));
				const int32 PendingMessageIndex = PendingChunk->PendingMessagePtr - PerChannelData[PendingChunk->ChannelId].PendingMessages.GetData();
				PerChannelData[PendingChunk->ChannelId].PendingMessages.RemoveAt(PendingMessageIndex);

				
				static_cast<BaseType&>(*this).HandleMessageReceived(MoveTemp(FullyReadMessage));
            }

			PendingChunk.Reset();
			// We've read the entire chunk, so we can reset the state machine
			SwitchState(EParserState::ParsingHeaderType);
		}
	}
}

template <typename Base>
void FReliableDataTransferProtocolReader<Base>::SwitchState(EParserState NewState)
{
	ParserState = NewState;
}