#ifndef OPENVINO_TEXT_PIPELINE_HPP
#define OPENVINO_TEXT_PIPELINE_HPP

#include "pipelines/text2text_pipeline.hpp"
#include "ov_genai.h" // Mocked OpenVINO GenAI header
#include <string>
#include <memory>
#include <openvino/genai/llm_pipeline.hpp>

class OVText2TextPipeline : public Text2TextPipeline {
public:
    OVText2TextPipeline(const std::string& model_path, const std::string& device);
    ~OVText2TextPipeline() override;

    GenerationResult operator()(const std::string& input) override;
    BackendType get_backend_type() const override;

private:
    std::string model_path_;
    std::string device_;
    std::shared_ptr<ov::genai::LLMPipeline> pipeline;
};

#endif // OPENVINO_TEXT_PIPELINE_HPP
