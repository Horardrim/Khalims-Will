VERSION = 1.3.0
TARGET=khalims-will

BUILD_OUTPUT_DIR = ../output
BUILD_OUTPUT_DIR_RELEASE = ../output_release

CXXFLAGS = -g -Wall -Werror
CXXFLAGS_TEST = -g -Wall -Werror -fprofile-arcs -ftest-coverage -DENABLE_UNIT_TEST
CXXFLAGS_RELEASE = -O3 -DNDEBUG -s -static-libgcc -static-libstdc++ -fstack-protector-strong -D_FORTIFY_SOURCE=2 -Wall -Wextra -Werror
LDFLAGS = -lgcov -fprofile-arcs -ftest-coverage
LIBS = -lcurl -lcpp-httplib -lpqxx -lpq -lhiredis -lrabbitmq -pthread
INCLUDE_PATH = -I ../main

VALGRIND_OUTPUT_FILE = $(TARGET).$(VERSION)_vg.log

BUILD_OUTPUT_DIR_RELEASE = ../output_release

all:
	@make -C main VERSION=$(VERSION) BUILD_OUTPUT_DIR=$(BUILD_OUTPUT_DIR) CXXFLAGS='$(CXXFLAGS)' TARGET=$(TARGET)  LIBS='$(LIBS)'

test:
	@make -C main VERSION=$(VERSION) BUILD_OUTPUT_DIR=$(BUILD_OUTPUT_DIR) CXXFLAGS='$(CXXFLAGS_TEST)' TARGET=$(TARGET) LDFLAGS='$(LDFLAGS)'  LIBS='$(LIBS)' INCLUDE_PATH='$(INCLUDE_PATH)'
	@valgrind --leak-check=full --log-file=$(VALGRIND_OUTPUT_FILE) ./output/$(TARGET).$(VERSION)

release:
	@make -C main VERSION=$(VERSION) BUILD_OUTPUT_DIR=$(BUILD_OUTPUT_DIR_RELEASE) CXXFLAGS='$(CXXFLAGS_RELEASE)' TARGET=$(TARGET) LDFLAGS='$(LDFLAGS_RELEASE)' LIBS='$(LIBS)'

clean:
	@rm -rf ${notdir $(BUILD_OUTPUT_DIR)} ${notdir $(BUILD_OUTPUT_DIR_RELEASE)} $(VALGRIND_OUTPUT_FILE) $(TARGET)_$(VERSION).tar
	@podman rmi hdm.io/$(TARGET):$(VERSION)

docker:
	@docker build --build-arg VERSION=$(VERSION) -t hdm/$(TARGET):$(VERSION) .

podman:
	@podman build --build-arg VERSION=$(VERSION) -t hdm.io/$(TARGET):$(VERSION) .
	@podman save -o $(TARGET)_$(VERSION).tar hdm.io/$(TARGET):$(VERSION)

.PHONY: all release clean docker

