#include "openvino_text_pipeline.hpp"
#include <iostream>
#include <vector>
#include <openvino/genai/llm_pipeline.hpp>

OVText2TextPipeline::OVText2TextPipeline(const std::string& model_path, const std::string& device)
    : model_path_(model_path), device_(device) {
    std::cout << "Initializing OVText2TextPipeline..." << std::endl;
    std::cout << "  Model Path: " << model_path_ << std::endl;
    std::cout << "  Device: " << device_ << std::endl;

    pipeline = std::make_shared<ov::genai::LLMPipeline>(ov::Core{}, model_path, device);
    std::cout << "OVText2TextPipeline initialized." << std::endl;
}

OVText2TextPipeline::~OVText2TextPipeline() {
    std::cout << "Destroying OVText2TextPipeline..." << std::endl;
}

GenerationResult OVText2TextPipeline::operator()(const std::string& input) {
    std::cout << "OVText2TextPipeline generating for input: \"" << input << "\"" << std::endl;
    auto result = pipeline->generate(input);
    std::cout << "OVText2TextPipeline generation complete. Output: " << result.text << std::endl;
    return {result.output_text};
}

BackendType OVText2TextPipeline::get_backend_type() const {
    return BackendType::OpenVINO;
}
