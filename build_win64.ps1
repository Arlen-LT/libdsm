param ($cmake_install)
echo "CMake Install Path: $cmake_install"

$vs2022_version=$(& "C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe" -version [17.0,18.0]  -property catalog_productDisplayVersion)
$vs2022_install=$(& "C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe" -version [17.0,18.0] -property installationPath)
echo "Visual Studio Version: $vs2022_version"
echo "Visual Studio Install Path: $vs2022_install"

$cmake="$cmake_install/bin/cmake.exe"
& $cmake --version
# $ninja="C:\tools\cmake-3.24.3-windows-x86_64\bin\ninja.exe"
# & $ninja --version
& $cmake --preset win64
pushd win64/build
& $cmake --build . --config Release
& $cmake --install .
popd
