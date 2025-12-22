#include <iostream>
#include "Parsers.hpp"
#include "Sample.hpp"
#include "FileReader.hpp"
#include "ParserFactory.hpp"


int main(int argc, char* argv[]) {
    auto parsers = makeParsers();
    FileReader fileReader("sample.txt");
    fileReader.start();
    std::vector<std::string> task;
    while (fileReader.getTask(task)) {
        MetricsSample sample{};
        for (const auto& line : task) {
            for (const auto& parser : parsers) {
                parser->parse(line, sample);
            }
        }
        std::cout << sample << std::endl;
    }
    return 0;
}
