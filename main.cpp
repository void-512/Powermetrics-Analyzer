#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <string>
#include <chrono>

#include "parsers.hpp"
#include "sample.hpp"

static bool isSampleHeader(const std::string& line) {
    return line.rfind("*** Sampled system activity", 0) == 0;
}

int main(int argc, char* argv[]) {
    std::istream* in = &std::cin;
    std::ifstream file;

    if (argc == 2) {
        file.open(argv[1]);
        if (!file) {
            std::cerr << "Failed to open file\n";
            return 1;
        }
        in = &file;
    }

    // Instantiate parsers
    std::vector<std::unique_ptr<LineParser>> parsers;
    parsers.emplace_back(std::make_unique<TimeStampParser>());
    parsers.emplace_back(std::make_unique<CpuPowerParser>());
    parsers.emplace_back(std::make_unique<GpuPowerParser>());
    parsers.emplace_back(std::make_unique<AnePowerParser>());
    parsers.emplace_back(std::make_unique<CombinedPowerParser>());

    MetricsSample sample{};
    bool in_sample = false;

    std::string line;
    while (std::getline(*in, line)) {
        if (isSampleHeader(line)) {
            if (in_sample) {
                // already have one sample → stop
                break;
            }
            in_sample = true;
        }

        if (!in_sample)
            continue;

        for (const auto& parser : parsers)
            parser->parse(line, sample);
    }

    if (!in_sample) {
        std::cerr << "No sample found\n";
        return 1;
    }

    // ---- Print results ----

    auto print_opt = [](const char* name, const std::optional<int>& v) {
        if (v)
            std::cout << name << ": " << *v << " mW\n";
        else
            std::cout << name << ": <not present>\n";
    };

    // Timestamp
    std::time_t t =
        std::chrono::system_clock::to_time_t(sample.timestamp);
    std::cout << "Timestamp: " << std::ctime(&t);

    print_opt("CPU Power", sample.cpu_power_mw);
    print_opt("GPU Power", sample.gpu_power_mw);
    print_opt("ANE Power", sample.ane_power_mw);
    print_opt("Combined Power", sample.combined_power_mw);

    return 0;
}
