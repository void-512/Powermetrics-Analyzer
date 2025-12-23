#include "Sample.hpp"

MetricsSample::MetricsSample() = default;

int MetricsSample::getCPUCount() const {
    return static_cast<int>(cpu_frequency.size());
}

std::chrono::system_clock::time_point MetricsSample::getTimestamp() const {
    return timestamp;
}

int MetricsSample::getCpuPowerMw() const {
    return cpu_power_mw;
}

int MetricsSample::getGpuPowerMw() const {
    return gpu_power_mw;
}

int MetricsSample::getAnePowerMw() const {
    return ane_power_mw;
}

int MetricsSample::getCombinedPowerMw() const {
    return combined_power_mw;
}

int MetricsSample::getCpuFrequency(int core) const {
    auto it = cpu_frequency.find(core);
    if (it != cpu_frequency.end()) {
        return it->second;
    }
    return 0;
}

double MetricsSample::getCpuActiveResidence(int core) const {
    auto it = cpu_active_residence.find(core);
    if (it != cpu_active_residence.end()) {
        return it->second;
    }
    return 0.0;
}

int MetricsSample::getGPUFrequency() const {
    return gpu_frequency;
}

int MetricsSample::getGPUActiveResidence() const {
    return gpu_active_residence;
}

void MetricsSample::setTimestamp(const std::chrono::system_clock::time_point& ts) {
    timestamp = ts;
}

void MetricsSample::setCpuPowerMw(int power) {
    cpu_power_mw = power;
}

void MetricsSample::setGpuPowerMw(int power) {
    gpu_power_mw = power;
}

void MetricsSample::setAnePowerMw(int power) {
    ane_power_mw = power;
}

void MetricsSample::setCombinedPowerMw(int power) {
    combined_power_mw = power;
}

void MetricsSample::setCpuFrequency(int core, int frequency) {
    cpu_frequency[core] = frequency;
}

void MetricsSample::setCpuActiveResidence(int core, double residence) {
    cpu_active_residence[core] = residence;
}

void MetricsSample::setGPUFrequency(int frequency) {
    gpu_frequency = frequency;
}

void MetricsSample::setGPUActiveResidence(double residence) {
    gpu_active_residence = residence;
}

std::ostream& operator<<(std::ostream& os, const MetricsSample& sample) {
    const int cpuCount = sample.getCPUCount();
    os << std::chrono::system_clock::to_time_t(sample.getTimestamp()) << ","
        << sample.getCpuPowerMw() << ","
        << sample.getGpuPowerMw() << ","
        << sample.getAnePowerMw() << ","
        << sample.getCombinedPowerMw() << ","
        << sample.getGPUFrequency() << ","
        << sample.getGPUActiveResidence();

    for (int core = 0; core < cpuCount; core++) {
        os << "," << sample.getCpuFrequency(core)
            << "," << sample.getCpuActiveResidence(core);
    }
    os << "\n";
    return os;
}