#include <iostream>
#include "Parsers.hpp"
#include "Sample.hpp"
#include "FileReader.hpp"

void exportToCsv(const std::vector<MetricsSample>& parsedData,
                 const std::string& filePath)
{
    if (parsedData.empty()) {
        throw std::runtime_error("No data to export");
    }

    std::ofstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open CSV file");
    }

    const int cpuCount = parsedData.front().getCPUCount();

    /* ---------- Header ---------- */
    file << "Timestamp,"
            << "CPU Power (mW),"
            << "GPU Power (mW),"
            << "ANE Power (mW),"
            << "Combined Power (mW),"
            << "GPU Frequency (MHz),"
            << "GPU Active (%)";

    for (int core = 0; core < cpuCount; core++) {
        file << ",CPU" << core << " Frequency (MHz)"
            << ",CPU" << core << " Active (%)";
    }
    file << "\n";

    /* ---------- Rows ---------- */
    for (const auto& sample : parsedData) {
        file << sample;
    }

    file.close();
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    } 
    FileReader fileReader(argv[1]);
    std::vector<MetricsSample> parsedData;
    ParseTask parseTask(parsedData);
    fileReader.start();
    std::vector<std::string> task;
    while (fileReader.getTask(task)) {
        parseTask.parse(task);
    }
    exportToCsv(parsedData, "output.csv");
    return 0;
}
