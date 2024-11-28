#!/usr/bin/bash

set -e

archive=${1:-T6_xstigl00_xsleza26}

mkdir $archive || true

make doc
cp doc/doc.pdf $archive

cp -r src CMakeLists.txt $archive

cd $archive
cat >./Makefile <<EOL
IMS_T6=src/*.cpp src/*.hpp
ALL=\$(IMS_T6)

.PHONY: build
build:
	if [ ! -f build/Makefile ]; then \\
		mkdir build; \\
		cd build && cmake .. -DCMAKE_BUILD_TYPE=Release \\
			-DCMAKE_CXX_COMPILER=g++-14.2; \\
	fi
	cd build && \$(MAKE)
	mv build/ims-t6 .

.PHONY: run
run: build
	./ims-t6

.PHONY: clean
clean:
	rm -r build obj ims-t6
EOL

echo 'target_link_libraries(ims-t6 PRIVATE -static-libstdc++)' \
    >> CMakeLists.txt

tar czf ../T6_xstigl00_xsleza26.tar.gz -- *

cd ..

rm -r T6_xstigl00_xsleza26/
