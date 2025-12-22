#include <iostream>
#include "Parsers.hpp"
#include "Sample.hpp"
#include "FileReader.hpp"

int main(int argc, char* argv[]) {
    FileReader fileReader("sample_long.txt");
    std::vector<MetricsSample> parsedData;
    ParseTask parseTask(parsedData);
    fileReader.start();
    std::vector<std::string> task;
    while (fileReader.getTask(task)) {
        parseTask.parse(task);
        std::cout << parsedData.back() << std::endl;
    }
    return 0;
}
