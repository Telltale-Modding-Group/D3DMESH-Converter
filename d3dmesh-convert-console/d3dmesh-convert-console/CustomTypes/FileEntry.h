#pragma once
#ifndef FILE_ENTRY_H
#define FILE_ENTRY_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Standard C++ Library
#include <string>
#include <filesystem>

//||||||||||||||||||||||||||||| FILE ENTRY |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| FILE ENTRY |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| FILE ENTRY |||||||||||||||||||||||||||||
//NOTE: This is NOT a data structure used by telltale.

/// <summary>
/// This is a custom type that holds common file information for IO operations.
/// </summary>
struct FileEntry
{
	std::string filePath;
	std::string fileNameWithExtension;
	std::string fileNameWithoutExtension;
	std::string fileExtension;
	std::string fileDirectory;
	unsigned long fileSize;

	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||
	//||||||||||||||||||||||||||||| CONSTRUCTORS |||||||||||||||||||||||||||||

	FileEntry()
	{
		filePath = {};
		fileNameWithExtension = {};
		fileNameWithoutExtension = {};
		fileExtension = {};
		fileDirectory = {};
		fileSize = 0;
	};

	FileEntry(std::filesystem::path& file)
	{
		filePath = file.string();
		fileNameWithExtension = file.filename().string();
		fileNameWithoutExtension = file.stem().string();
		fileExtension = file.extension().string();
		fileDirectory = file.parent_path().string();
		fileSize = std::filesystem::file_size(file);
	};

	FileEntry(std::filesystem::directory_entry directoryEntry)
	{
		filePath = directoryEntry.path().string();
		fileNameWithExtension = directoryEntry.path().filename().string();
		fileNameWithoutExtension = directoryEntry.path().stem().string();
		fileExtension = directoryEntry.path().extension().string();
		fileDirectory = directoryEntry.path().parent_path().string();
		fileSize = std::filesystem::file_size(directoryEntry.path());
	};
};

#endif