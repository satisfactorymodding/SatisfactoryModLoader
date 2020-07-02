#include "ZipFile.h"

size_t ReadZipArchiveFunc(void* Opaque, mz_uint64 FileOffset, void* ReadBuffer, size_t Amount) {
	IFileHandle* FileHandle = static_cast<IFileHandle*>(Opaque);
	const int64 BytesToRead = static_cast<int64>(Amount);
	const int64 RequiredOffset = static_cast<int64>(FileOffset);
	const int64 CurrentOffset = FileHandle->Tell();
	if (CurrentOffset != RequiredOffset)
		FileHandle->Seek(RequiredOffset);
	//Try to read with suggested amount first
	if (FileHandle->Read(static_cast<uint8*>(ReadBuffer), BytesToRead)) {
		return Amount;
	}
	//Not enough bytes to actually read, try to read Size - Offset
	const int64 MaxBytesToRead = FMath::Min(FileHandle->Size() - FileHandle->Tell(), BytesToRead);
	if (FileHandle->Read(static_cast<uint8*>(ReadBuffer), MaxBytesToRead)) {
		return static_cast<size_t>(MaxBytesToRead);
	}
	//cannot read anything, return 0
	return 0;
}

size_t ExtractZipArchiveFunc(void *Opaque, mz_uint64 FileOffset, const void* WriteBuffer, size_t WriteAmount) {
	IFileHandle* FileHandle = static_cast<IFileHandle*>(Opaque);
	const int64 BytesToWrite = static_cast<int64>(WriteAmount);
	const int64 RequiredOffset = static_cast<int64>(FileOffset);
	const int64 CurrentOffset = FileHandle->Tell();
	if (CurrentOffset != RequiredOffset)
		FileHandle->Seek(RequiredOffset);
	//Just write required amount
	const bool Result = FileHandle->Write(static_cast<const uint8*>(WriteBuffer), BytesToWrite);
	return Result ? WriteAmount : 0;
}

FZipFile::FZipFile(TUniquePtr<IFileHandle> Handle) : FileHandle(std::move(Handle)), InitSuccess(false) {
	FMemory::Memzero(ZipArchive);
	ZipArchive.m_pIO_opaque = FileHandle.Get();
	ZipArchive.m_pRead = &ReadZipArchiveFunc;
}

FZipFile::~FZipFile() {
	if (InitSuccess) {
		mz_zip_reader_end(&ZipArchive);
	}
}

bool FZipFile::InitArchive() {
	InitSuccess = static_cast<bool>(mz_zip_reader_init(&ZipArchive, FileHandle->Size(), 0));
	return InitSuccess;
}


uint32 FZipFile::ComputeFileIndex(const ANSICHAR* FileName) {
	uint32 ResultFileIndex;
	bool Result = static_cast<bool>(mz_zip_reader_locate_file_v2(&ZipArchive, FileName, NULL, 0, &ResultFileIndex));
	return Result ? ResultFileIndex : ZIP_NO_FILE_INDEX;
}
	
uint32 FZipFile::LocateFileIndex(const FString& FilePath) {
	uint32* ExistingIndex = FileNameToIndex.Find(FilePath);
	if (ExistingIndex)
		return *ExistingIndex;
	const uint32 NewIndex = ComputeFileIndex(TCHAR_TO_ANSI(*FilePath));
	FileNameToIndex.Add(FilePath, NewIndex);
	return NewIndex;
}

bool FZipFile::FileExists(const FString& FilePath) {
	return LocateFileIndex(FilePath) != ZIP_NO_FILE_INDEX;
}
	
mz_zip_archive_file_stat FZipFile::StatFile(const FString& FilePath) {
	mz_zip_archive_file_stat FileStat{};
	const uint32 FileIndex = LocateFileIndex(FilePath);
	if (FileIndex != ZIP_NO_FILE_INDEX)
		mz_zip_reader_file_stat(&ZipArchive, FileIndex, &FileStat);
	return FileStat;
}

bool FZipFile::ExtractFile(const FString& FilePath, IFileHandle* OutFileHandle) {
	const uint32 FileIndex = LocateFileIndex(FilePath);
	if (FileIndex == ZIP_NO_FILE_INDEX)
		return false;
	bool Result = static_cast<bool>(mz_zip_reader_extract_to_callback(&ZipArchive, FileIndex, &ExtractZipArchiveFunc, OutFileHandle, 0));
	return Result && OutFileHandle->Flush();
}

bool FZipFile::ReadFileToBuffer(const FString& FilePath, void* Buffer, SIZE_T BufferSize) {
	const uint32 FileIndex = LocateFileIndex(FilePath);
	if (FileIndex == ZIP_NO_FILE_INDEX)
		return false;
	return static_cast<bool>(mz_zip_reader_extract_to_mem(&ZipArchive, FileIndex, Buffer, BufferSize, 0));
}

bool FZipFile::ReadFileToString(const FString& FilePath, FString& OutString) {
	const mz_zip_archive_file_stat FileStat = StatFile(FilePath);
	if (FileStat.m_uncomp_size == 0)
		return false; //file doesn't exist
	//Create buffer (extra 4k for safety too)
	const SIZE_T BufferSize = FileStat.m_uncomp_size;
	void* ExtractBuffer = FMemory::Malloc(BufferSize);
	//Read file into buffer, then convert it to string
	const bool Success = ReadFileToBuffer(FilePath, ExtractBuffer, BufferSize);
	if (Success) {
		FFileHelper::BufferToString(OutString, static_cast<uint8*>(ExtractBuffer), BufferSize);
	}
	FMemory::Free(ExtractBuffer);
	return Success;
}


TSharedPtr<FZipFile> CreateZipArchiveReader(const FString& FilePath) {
	TUniquePtr<IFileHandle> FileHandle = TUniquePtr<IFileHandle>(FPlatformFileManager::Get().GetPlatformFile().OpenRead(*FilePath));
	if (FileHandle == nullptr) {
		SML::Logging::error(TEXT("CreateZipArchiveReader failed for "), *FilePath, TEXT(": Cannot open file"));
		return nullptr;
	}
	TSharedRef<FZipFile> ZipHandle = MakeShareable(new FZipFile(std::move(FileHandle)));
	if (!ZipHandle->InitArchive()) {
		const FString LastError = mz_zip_get_error_string(ZipHandle->GetLastError());
		SML::Logging::error(TEXT("CreateZipArchiveReader failed for "), *FilePath, TEXT(": Corrupted zip file (Last Error: "), *LastError, TEXT(")"));
		return nullptr;
	}
	return ZipHandle;
}
