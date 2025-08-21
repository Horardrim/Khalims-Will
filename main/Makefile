
TARGET = khalims-will

SRC := $(shell find . -type f -name '*.cxx')
OBJS := $(SRC:./%.cxx=./$(BUILD_OUTPUT_DIR)/%.o)
DEPS := $(SRC:./%.cxx=./$(BUILD_OUTPUT_DIR)/%.d)

all: ${BUILD_OUTPUT_DIR}/${TARGET}.${VERSION}

ifneq ($(MAKECMDGOALS),clean)
-include $(DEPS)
endif

${BUILD_OUTPUT_DIR}/%.d: %.cxx
	@mkdir -p $(BUILD_OUTPUT_DIR)
	$(CXX) -MM -MT "$(BUILD_OUTPUT_DIR)/$(subst .cxx,.o,${notdir $<}) $(BUILD_OUTPUT_DIR)/$(subst .cxx,.d,${notdir $<})" -MF "$(subst .cxx,.d,${BUILD_OUTPUT_DIR}/${notdir $<})" $<

$(BUILD_OUTPUT_DIR)/%.o: %.cxx
	$(CXX) $(CXXFLAGS) $(INCLUDE_PATH) -c $< -o $(BUILD_OUTPUT_DIR)/$(subst .cxx,.o,${notdir $<})

${BUILD_OUTPUT_DIR}/${TARGET}.${VERSION}: ${OBJS}
	${CXX} $(CXXFLAGS)  -o $@  $(addprefix $(BUILD_OUTPUT_DIR)/,${notdir $^})

.PHONY: all
