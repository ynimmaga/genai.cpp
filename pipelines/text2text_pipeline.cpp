#include "text2text_pipeline.hpp"
#include "backends/onnx/onnx_text_pipeline.hpp"
#include "backends/openvino/openvino_text_pipeline.hpp"
#include <stdexcept>

// Factory function implementation
std::shared_ptr<Text2TextPipeline> create_pipeline(
    BackendType backend,
    const std::string& model_path,
    const std::string& device) {

    switch (backend) {
        case BackendType::ONNXRuntime:
            return std::make_shared<ORTText2TextPipeline>(model_path, device);
        case BackendType::OpenVINO:
            return std::make_shared<OVText2TextPipeline>(model_path, device);
        default:
            throw std::invalid_argument("Unsupported backend type provided to create_pipeline.");
    }
}
