#include "kdmapper.hpp"

HANDLE iqvw64e_device_handle;

auto read_file(const std::string filename) -> std::vector<uint8_t>
{
	SetConsoleTitle("qtx kernel device manager");

	std::ifstream stream(filename, std::ios::binary);

	std::vector<uint8_t> buffer{ };

	buffer.assign((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());

	stream.close();

	return buffer;
}
std::vector<uint8_t> RawData
 {
	//bytes
};


int wmain(const int argc, wchar_t** argv) {
	iqvw64e_device_handle = intel_driver::Load();

	SetConsoleTitle( "DDM" );

	if (iqvw64e_device_handle == INVALID_HANDLE_VALUE)
		return -1;

	/*std::vector<uint8_t> raw_image = read_file("dolphin_x64.sys");*/

	NTSTATUS exitCode = 0;
	if (!kdmapper::MapDriver(iqvw64e_device_handle, RawData.data(), 0, 0, false, true, true, true, NULL, &exitCode)) {
		Log(L"[-] Failed to map kernel device" << std::endl);
		intel_driver::Unload(iqvw64e_device_handle);
		return -1;
	}

	if (!intel_driver::Unload(iqvw64e_device_handle)) {
		Log(L"[-] Warning failed to fully unload vulnerable driver " << std::endl);
	}
	Log(L"[/] Successfully completed operation." << std::endl);

	MessageBoxA(0, "Successfully mapped virtual device.", "dolphin device manager", 0);

	std::getchar();
}