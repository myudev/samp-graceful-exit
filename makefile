# -
# Setup test requirements
# -

test-setup:
	cd test && sampctl server ensure
	sampctl package ensure

# -
# Run Tests
# -

test-native:
	sampctl package build
	cd test && sampctl server run

test-container:
	sampctl package build
	cd test && sampctl server run --container

# -
# Build inside container
# -

build-container:
	rm -rf build
	docker build -t southclaws/samp-graceful-exit-build .
	docker run -v $(shell pwd)/test/plugins:/root/test/plugins southclaws/samp-graceful-exit-build

# this make target is only run inside the container
build-inside:
	cd build && cmake .. && make
