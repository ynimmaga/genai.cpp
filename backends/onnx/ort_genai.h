#ifndef ORT_GENAI_H
#define ORT_GENAI_H

#include <string>
#include <vector>
#include <memory> // For std::unique_ptr
#include <iostream> // For mock output

namespace Oga {

class Config {
public:
    static std::unique_ptr<Config> Create(const char* model_path_cstr) {
        std::cout << "[Mock OrtGenAI] OgaConfig::Create with model_path: " << model_path_cstr << std::endl;
        return std::make_unique<Config>();
    }
    void append_provider(const std::string& config_device) {
        std::cout << "[Mock OrtGenAI] OgaConfig::append_provider with device: " << config_device << std::endl;
    }
    // Add other necessary methods if any
};

class Model {
public:
    static std::unique_ptr<Model> Create(Config& /*config*/) {
        std::cout << "[Mock OrtGenAI] OgaModel::Create" << std::endl;
        return std::make_unique<Model>();
    }
};

class Tokenizer {
public:
    static std::unique_ptr<Tokenizer> Create(Model& /*model*/) {
        std::cout << "[Mock OrtGenAI] OgaTokenizer::Create" << std::endl;
        return std::make_unique<Tokenizer>();
    }
    std::vector<int> Encode(const char* /*text*/) const {
        std::cout << "[Mock OrtGenAI] OgaTokenizer::Encode" << std::endl;
        return {101, 102, 103}; // Dummy tokens
    }
    std::string Decode(const std::vector<int>& tokens) const {
        std::cout << "[Mock OrtGenAI] OgaTokenizer::Decode for " << tokens.size() << " tokens" << std::endl;
        std::string decoded_text = "";
        for (int tok : tokens) {
            decoded_text += "tok" + std::to_string(tok) + " ";
        }
        return decoded_text;
    }
    // Mocking ApplyChatTemplate as seen in the image
    std::vector<int> ApplyChatTemplate(const char* /*template_name*/, const char* input_cstr, bool /*add_generation_prompt*/, std::vector<int>& /*seq_ref - assuming this modifies seq*/) {
        std::cout << "[Mock OrtGenAI] OgaTokenizer::ApplyChatTemplate with input: " << input_cstr << std::endl;
        // Simulate modifying seq or returning a new sequence
        return {201, 202, 203}; // Dummy templated tokens
    }
};

class Sequences {
public:
    static std::unique_ptr<Sequences> Create() {
         std::cout << "[Mock OrtGenAI] OgaSequences::Create" << std::endl;
        return std::make_unique<Sequences>();
    }
    // Add methods if needed, based on how `*seq` is used in `tokenizer->AppendTokenSequences(*seq)`
    // For now, we'll assume AppendTokenSequences takes the vector directly for simplicity in mock
};


class GeneratorParams {
public:
    static std::unique_ptr<GeneratorParams> Create(Model& /*model*/) {
        std::cout << "[Mock OrtGenAI] OgaGeneratorParams::Create" << std::endl;
        return std::make_unique<GeneratorParams>();
    }
    void SetSearchOption(const std::string& /*option_name*/, double /*value*/) {
        std::cout << "[Mock OrtGenAI] OgaGeneratorParams::SetSearchOption (double)" << std::endl;
    }
     void SetSearchOption(const std::string& /*option_name*/, int value) {
        std::cout << "[Mock OrtGenAI] OgaGeneratorParams::SetSearchOption (int): " << value << std::endl;
    }
    // Add other SetSearchOption overloads if necessary
};

class Generator {
private:
    int current_token_idx = 0;
    std::vector<int> generated_sequence_ = {301, 302, 303, 304, 305}; // Dummy full sequence
    std::vector<int> current_batch_sequence_; // For GetSequenceData

public:
    Generator(Model& /*model*/, GeneratorParams& /*params*/) {
         std::cout << "[Mock OrtGenAI] OgaGenerator constructor" << std::endl;
    }

    static std::unique_ptr<Generator> Create(Model& model, GeneratorParams& params) {
        std::cout << "[Mock OrtGenAI] OgaGenerator::Create" << std::endl;
        return std::make_unique<Generator>(model, params);
    }

    // As per image: generator->AppendTokenSequences(*seq)
    // Assuming seq is a vector<int> for simplicity in mock
    void AppendTokenSequences(const std::vector<int>& /*token_sequence*/) {
        std::cout << "[Mock OrtGenAI] OgaGenerator::AppendTokenSequences" << std::endl;
        current_token_idx = 0; // Reset for new generation
    }

    bool IsDone() {
        bool done = current_token_idx >= generated_sequence_.size();
        std::cout << "[Mock OrtGenAI] OgaGenerator::IsDone -> " << (done ? "true" : "false") << std::endl;
        return done;
    }

    void GenerateNextToken() {
        std::cout << "[Mock OrtGenAI] OgaGenerator::GenerateNextToken" << std::endl;
        if (current_token_idx < generated_sequence_.size()) {
            current_batch_sequence_ = { generated_sequence_[current_token_idx] }; // Simulate one token at a time for GetSequenceData
            current_token_idx++;
        } else {
            current_batch_sequence_.clear();
        }
    }

    // int tok = generator->GetSequenceData(0).back();
    // Assuming GetSequenceData(0) returns data for the first (and only) sequence in the batch
    // And .back() gets the last token.
    const std::vector<int>& GetSequenceData(int /*batch_index*/) const {
         std::cout << "[Mock OrtGenAI] OgaGenerator::GetSequenceData for batch_index 0" << std::endl;
        return current_batch_sequence_;
    }
};

} // namespace Oga

#endif // ORT_GENAI_H
