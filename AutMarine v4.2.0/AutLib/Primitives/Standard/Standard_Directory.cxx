#include <Standard_Directory.hxx>
#include <Windows.h>

void AutLib::CreateDirectoryRecursively(const Standard_String directory)
{
	static const Standard_String separators("\\/");

	// If the specified directory name doesn't exist, do our thing
	DWORD fileAttributes = GetFileAttributes(directory.c_str());
	if (fileAttributes == INVALID_FILE_ATTRIBUTES) {

		// Recursively do it all again for the parent directory, if any
		std::size_t slashIndex = directory.find_last_of(separators);
		if (slashIndex != std::wstring::npos) {
			CreateDirectoryRecursively(directory.substr(0, slashIndex));
		}

		// Create the last directory on the path (the recursive calls will have taken
		// care of the parent directories by now)
		BOOL result = CreateDirectory(directory.c_str(), nullptr);
		if (result == FALSE) {
			throw std::runtime_error("Could not create directory");
		}

	}
	else { // Specified directory name already exists as a file or directory

		bool isDirectoryOrJunction =
			((fileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0) ||
			((fileAttributes & FILE_ATTRIBUTE_REPARSE_POINT) != 0);

		if (!isDirectoryOrJunction) {
			throw std::runtime_error(
				"Could not create directory because a file with the same name exists"
			);
		}

	}
}