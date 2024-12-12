#include <iostream>
#include <unordered_map>
#include <vector>
#include <cmath>
std::unordered_map<std::string, bool> stop_words_map = {
    {"the", true}, {"a", true}, {"an", true}, {"I", true},
    {"you", true}, {"he", true}, {"she", true}, {"it", true},
    {"and", true}, {"or", true}, {"but", true}, {"in", true},
    {"on", true}, {"at", true}, {"by", true},
    {"is", true}, {"are", true}, {"was", true}, {"were", true}
};
int is_stop_word(std::string& word) {
    if (stop_words_map.find(word) != stop_words_map.end()) {
        return 1;
    }
    return 0;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int training_quantity, test_quantity;
    std::cin >> training_quantity >> test_quantity;
    std::unordered_map<std::string,int> class0;
    std::unordered_map<std::string,int> class1;
    size_t class_0_word_count = 0;
    size_t class_1_word_count = 0;
    for (int i = 0; i < training_quantity; i++) {
        size_t* word_count;
        std::string word;
        int class_type;
        std::unordered_map<std::string,int>* current_class;
        std::cin >> class_type;
        if (class_type == 0) {
            current_class = &class0;
            word_count  = &class_0_word_count;
        }
        else {
            current_class = &class1;
            word_count  = &class_1_word_count;
        }
        std::cin.ignore();
        char splitter = ' ';
        while (splitter != '\n') {
            std::cin >> word;
            splitter = std::cin.get();
            if (splitter == '\n') {
                if (word[word.length() - 1] == '.') {
                    word.pop_back();
                }
            }
            if (is_stop_word(word)) {
                continue;
            }
            (*word_count)++;
            std::unordered_map<std::string,int>::iterator it = (*current_class).find(word);
            if (it == (*current_class).end()) {
                (*current_class)[word] = 1;
            }
            else {
                (*current_class)[word]++;
            }
        }
    }
    size_t common_count_all = class_0_word_count + class_1_word_count;
    double p0 = class_0_word_count * 1.0 / common_count_all;
    double p1 = class_1_word_count * 1.0 / common_count_all;
    std::string word;
    for (int i = 0; i < test_quantity; i++){
        char splitter = ' ';
        double p_in_0 = std::log(p0);
        double p_in_1 = std::log(p1);
        while (splitter  != '\n' && splitter != EOF) {
            std::cin >> word;
            splitter = std::cin.get();
            if (splitter == '\n') {
                if (word[word.length() - 1] == '.') {
                    word.pop_back();
                }
            }
            if (is_stop_word(word)) {
                continue;
            }
            auto w_in_0 = class0.find(word);
            auto w_in_1 = class1.find(word);
            size_t word_count_0 = 0;
            size_t word_count_1 = 0;
            int common_count =  0;
            if (w_in_0 != class0.end()) {
                    word_count_0 = w_in_0->second;
                    common_count += word_count_0;
            }
            if (w_in_1 != class1.end()) {
                word_count_1 = w_in_1->second;
                common_count += word_count_1;
            }
            double p_common = double(common_count) / common_count_all;
            p_in_0 += std::log((double)(word_count_0 + 1)/(p_common + class0.size()));
            p_in_1 += std::log((double)(word_count_1 + 1)/(p_common + class1.size()));
        }
        if (p_in_0 > p_in_1) {
            std::cout << 0 << '\n';
        }
        else {
            std::cout << 1 << '\n';
        }
        std::cout.flush();
    }
    return 0;
}
