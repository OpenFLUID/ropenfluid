
all:
	mkdir -p _build ; \
	cd _build ; \
	cmake .. -DR_LIBRARIES="${LIBR}" -DR_INCLUDES=${R_INCLUDE_DIR} -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=.. ; \
	make install

clean:
	rm -rf _build
	rm -rf *.so

