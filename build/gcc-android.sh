function download3rd(){
	cd ../ext
	if [ ! -d "${2}" ] 
	then
		if [ ! -f "${2}.tar.gz" ] 
		then
			curl ${1} -o ${2}.tar.gz
		fi
		tar -xzvf ${2}.tar.gz
	fi
	cd ../build
}
function build(){
	if [ ! -d "${1}" ]; then
		mkdir ${1}
		cd ${1}
		cmake ../../ext/${1} -G "${3}" -DCMAKE_TOOLCHAIN_FILE=${2} ${4} -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../../output
	else
		cd ${1}
	fi
	cmake --build ./ --target install
	cd ..
}
function buildprj(){
	if [ ! -d "${1}" ]; then
		mkdir ${1}
		cd ${1}
		cmake ../../generate -G "${3}" -DCMAKE_TOOLCHAIN_FILE=${2} ${4} -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../../output
	else
		cd ${1}
	fi
	cmake --build ./ --target install
	cd ..
}

# download3rd ftp://ftp-osl.osuosl.org/pub/libpng/src/libpng16/libpng-1.6.34.tar.gz libpng-1.6.34
# download3rd https://www.zlib.net/zlib-1.2.11.tar.gz zlib-1.2.11
# build zlib-1.2.11 ../../cmake/imx6qwin.cmake "Unix Makefiles"
# build libpng-1.6.34 ../../cmake/imx6qwin.cmake "Unix Makefiles" -DZLIBROOT=../../output
buildprj android ../../cmake/android.cmake "Unix Makefiles" 
