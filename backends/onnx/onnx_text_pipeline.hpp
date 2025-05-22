#ifndef ONNX_TEXT_PIPELINE_HPP
#define ONNX_TEXT_PIPELINE_HPP

#include "pipelines/text2text_pipeline.hpp"
#include "ort_genai.h" // Mocked ONNX GenAI header
#include <string>
#include <memory>

class ORTText2TextPipeline : public Text2TextPipeline {
public:
    ORTText2TextPipeline(const std::string& model_path, const std::string& device);
    ~ORTText2TextPipeline() override;

    GenerationResult operator()(const std::string& input) override;
    BackendType get_backend_type() const override;

private:
    std::string model_path_;
    std::string device_;

    // Members based on the image and mocked ort_genai.h
    std::unique_ptr<Oga::Config> config_;
    std::unique_ptr<Oga::Model> model_;
    std::unique_ptr<Oga::Tokenizer> tokenizer_;
    std::unique_ptr<Oga::GeneratorParams> params_;
    std::unique_ptr<Oga::Generator> generator_;
};

#endif // ONNX_TEXT_PIPELINE_HPP
