# Mock FindOvGenAI.cmake
# In a real scenario, this would locate the OpenVINO GenAI headers and libraries.

message(STATUS "Looking for OvGenAI (mocked)")

# Set placeholder paths
set(OV_GENAI_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/backends/openvino") # Points to our mock header
set(OV_GENAI_LIBRARIES "ov_genai_mock_lib") # Placeholder library name

if(OV_GENAI_INCLUDE_DIRS AND EXISTS "${OV_GENAI_INCLUDE_DIRS}/ov_genai.h")
    set(OvGenAI_FOUND TRUE)
    message(STATUS "Found OvGenAI (mocked): TRUE")
    message(STATUS "  OvGenAI_INCLUDE_DIRS: ${OV_GENAI_INCLUDE_DIRS}")
    message(STATUS "  OvGenAI_LIBRARIES: ${OV_GENAI_LIBRARIES}")
else()
    set(OvGenAI_FOUND FALSE)
    message(STATUS "Found OvGenAI (mocked): FALSE - Mock header not found where expected.")
endif()

if(OvGenAI_FOUND)
    if(NOT TARGET OvGenAI::ov_genai)
        add_library(OvGenAI::ov_genai INTERFACE IMPORTED)
        set_target_properties(OvGenAI::ov_genai PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${OV_GENAI_INCLUDE_DIRS}")
        # target_link_libraries(OvGenAI::ov_genai INTERFACE ov_genai_mock_lib) # If linking a real lib
    endif()
endif()
