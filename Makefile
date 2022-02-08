.PHONY: help debug release dist clean deps coconut

help:
	@echo "Targets:"
	@echo "  debug  : Generate build artifacts for a debug build in build-debug"
	@echo "  release: Generate build artifacts for a release build in build-release"
	@echo "  dist   : Pack civicc and coconut into a tar.gz file. Use this for creating a submission"
	@echo "  clean  : Remove all build directories and created dist files"

coconut:
	make -C coconut

debug: coconut
	@cmake -DCMAKE_BUILD_TYPE=Debug -S ./ -B build-$@/

release: coconut
	@cmake -DCMAKE_BUILD_TYPE=Release -S ./ -B build-$@/


dist:
	bash scripts/dist.sh

clean:
	rm -f *.tar*
	rm -rf build*/
