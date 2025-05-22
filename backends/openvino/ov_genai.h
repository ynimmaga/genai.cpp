#ifndef OV_GENAI_H
#define OV_GENAI_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>

// Mocked OpenVINO GenAI (Ova) types and functions
// This is a conceptual parallel to ort_genai.h

namespace Ova {

class Config {
public:
    static std::unique_ptr<Config> Create(const char* model_path_cstr) {
        std::cout << "[Mock OvGenAI] OvaConfig::Create with model_path: " << model_path_cstr << std::endl;
        return std::make_unique<Config>();
    }
    void set_device(const std::string& device_name) {
        std::cout << "[Mock OvGenAI] OvaConfig::set_device: " << device_name << std::endl;
    }
};

class Model {
public:
    static std::unique_ptr<Model> Create(Config& /*config*/) {
        std::cout << "[Mock OvGenAI] OvaModel::Create" << std::endl;
        return std::make_unique<Model>();
    }
};

class Tokenizer {
public:
    static std::unique_ptr<Tokenizer> Create(Model& /*model*/) {
        std::cout << "[Mock OvGenAI] OvaTokenizer::Create" << std::endl;
        return std::make_unique<Tokenizer>();
    }
    std::vector<int> Encode(const std::string& text) const {
        std::cout << "[Mock OvGenAI] OvaTokenizer::Encode for: " << text << std::endl;
        return {701, 702, 703}; // Dummy tokens
    }
    std::string Decode(const std::vector<int>& tokens) const {
        std::cout << "[Mock OvGenAI] OvaTokenizer::Decode for " << tokens.size() << " tokens" << std::endl;
        std::string decoded_text = "";
        for (int tok : tokens) {
            decoded_text += "ov_tok" + std::to_string(tok) + " ";
        }
        return decoded_text;
    }
    std::string ApplyChatTemplate(const std::string& /*template_name*/, const std::string& input) {
        std::cout << "[Mock OvGenAI] OvaTokenizer::ApplyChatTemplate with input: " << input << std::endl;
        return "Processed by OV Template: " + input;
    }
};

class GeneratorParams {
public:
    static std::unique_ptr<GeneratorParams> Create(Model& /*model*/) {
        std::cout << "[Mock OvGenAI] OvaGeneratorParams::Create" << std::endl;
        return std::make_unique<GeneratorParams>();
    }
    void SetSearchOption(const std::string& option_name, int value) {
        std::cout << "[Mock OvGenAI] OvaGeneratorParams::SetSearchOption: " << option_name << " = " << value << std::endl;
    }
};

class Generator {
private:
    int current_token_idx = 0;
    std::vector<int> generated_sequence_ = {801, 802, 803, 804, 805}; // Dummy full sequence
    std::vector<int> current_batch_token_;

public:
    Generator(Model& /*model*/, GeneratorParams& /*params*/) {
         std::cout << "[Mock OvGenAI] OvaGenerator constructor" << std::endl;
    }
    static std::unique_ptr<Generator> Create(Model& model, GeneratorParams& params) {
        std::cout << "[Mock OvGenAI] OvaGenerator::Create" << std::endl;
        return std::make_unique<Generator>(model, params);
    }
    void SetInputTokens(const std::vector<int>& /*token_ids*/) {
        std::cout << "[Mock OvGenAI] OvaGenerator::SetInputTokens" << std::endl;
        current_token_idx = 0; // Reset for new generation
    }
    bool IsDone() {
        bool done = current_token_idx >= generated_sequence_.size();
        std::cout << "[Mock OvGenAI] OvaGenerator::IsDone -> " << (done ? "true" : "false") << std::endl;
        return done;
    }
    int GenerateNextToken() {
        std::cout << "[Mock OvGenAI] OvaGenerator::GenerateNextToken" << std::endl;
        if (!IsDone()) {
            current_batch_token_ = { generated_sequence_[current_token_idx] };
            current_token_idx++;
            return current_batch_token_.back();
        }
        return -1; // End of sequence token or error
    }
};

} // namespace Ova

#endif // OV_GENAI_H
