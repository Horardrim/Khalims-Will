VERSION = 1.0.0
TARGET=khalims-will
BUILD_OUTPUT_DIR = ../output
CXXFLAGS = -g -Wall -Werror
CXXFLAGS_TEST = -g -Wall -Werror -DENABLE_UNIT_TEST
CXXFLAGS_RELEASE = -O3 -DNDEBUG -s -static-libgcc -static-libstdc++ -fstack-protector-strong -D_FORTIFY_SOURCE=2 -Wall -Wextra -Werror
BUILD_OUTPUT_DIR_RELEASE = ../output_release

all:
	@make -C main VERSION=$(VERSION) BUILD_OUTPUT_DIR=$(BUILD_OUTPUT_DIR) CXXFLAGS='$(CXXFLAGS)' TARGET=$(TARGET)

test:
	@make -C main VERSION=$(VERSION) BUILD_OUTPUT_DIR=$(BUILD_OUTPUT_DIR) CXXFLAGS='$(CXXFLAGS_TEST)' TARGET=$(TARGET)

release:
	@make -C main VERSION=$(VERSION) BUILD_OUTPUT_DIR=$(BUILD_OUTPUT_DIR_RELEASE) CXXFLAGS='$(CXXFLAGS_RELEASE)' TARGET=$(TARGET)

clean:
	@rm -rf ${notdir $(BUILD_OUTPUT_DIR)} ${notdir $(BUILD_OUTPUT_DIR_TEST)} ${notdir $(BUILD_OUTPUT_DIR_RELEASE)}

docker:
	@docker build --build-arg VERSION=$(VERSION) -t hdm/$(TARGET):$(VERSION) .

.PHONY: all release clean docker

