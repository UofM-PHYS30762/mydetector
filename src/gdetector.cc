#include "gdetector/gdetector.h"

#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <utility>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>

namespace detector {
/*
 * # Example implementation of [UUID4]
 *
 * In short, UUIDv4 is a 128-bit binary.
 * The first 48 bits, random_a, should be randomly generated.
 * The next 4 bits are the version number, ver, 0b0100, 4.
 * The next 12 bits, random_b should also be randomly generated.
 * In our implementation, the above 64 bits are called upper.
 * The next 2 bits should be variant, var, 0b10.
 * The remaining 62 bits, random_c should be randomly generated.
 * The last 64 bits are called lower in our implementation.
 *
 *   [UUID4]: https://datatracker.ietf.org/doc/html/rfc9562.html#section-5.4
 *
 */
std::string UUID4() {
  // Use a proper random engine seeded with random_device
  static std::random_device rd;
  static std::mt19937_64 gen(rd());

  static std::uniform_int_distribution<uint64_t> dist;

  uint64_t upper = dist(gen); // random_a, ver and random_b
  uint64_t lower = dist(gen); // var and random_c

  // Set version (0b0100, 4)
  upper = (upper & 0xFFFFFFFFFFFF0FFFULL) | 0x0000000000004000ULL;
  // Set variant (0b10)
  lower = (lower & 0x3FFFFFFFFFFFFFFFULL) | 0x8000000000000000ULL;

  // Convert hex binary to string
  std::ostringstream ss;
  ss << std::hex;
  ss << std::setw(2) << upper;
  ss << std::setw(2) << lower;
  std::string result = ss.str();

  // Insert separators
  // 8-4-4-4-12 => 8-12-16-20 => 8-13-18-23
  std::vector<int> insert_index = {8, 13, 18, 23};
  for (auto i : insert_index) {
    result.insert(i, 1, '-');
  }

  return result;
}

// @class Source
std::vector<std::string> Source::available_sources_ = {"Na-22", "Cs-136",
                                                       "Co-92"};
// Constructor and destructors
Source::Source() { id_ = UUID4(); }
Source::Source(const std::string &name, const time_t &date,
               const double &activity) {
  set_name(name);
  set_date(date);
  set_activity(activity);
  id_ = UUID4();
}
Source::~Source() {
  std::cout << "Releasing memory in Source " << id_ << std::endl;
}
// Getters and setters
std::string Source::name() const { return name_; }
time_t Source::date() const { return date_; }
double Source::activity() const { return activity_; }
std::string Source::id() const { return id_; }
std::vector<std::string> Source::available_sources() {
  return available_sources_;
}

void Source::set_name(const std::string &name) {
  const bool available =
    std::find(available_sources_.begin(), available_sources_.end(), name) != available_sources_.end();
      // std::ranges::find(available_sources_, name) != available_sources_.end();
  if (!available) {
    throw std::invalid_argument("Source name is not available");
  }
  name_ = name;
}
void Source::set_date(const time_t &date) { date_ = date; }
void Source::set_activity(const double &activity) { activity_ = activity; }
void Source::set_available_sources(const std::vector<std::string> &sources) {
  available_sources_ = sources;
}

// Printers
std::ostream &operator<<(std::ostream &os, const Source &source) {
  os << "Source name: " << source.name_ << "\n"
     << "Acquisition date: " << ctime(&source.date_)
     << "Activity: " << source.activity_ << " Bq/kg" << "\n"
     << "ID: " << source.id_ << "\n";

  return os;
}
// @class Detector
std::vector<std::string> Detector::available_detectors_ = {"Scintillator", "Geiger", "Germanium"};
// Constructors and destructors
Detector::Detector(const std::string &type) {
  set_type(type);
}
Detector::~Detector() {
  std::cout << "Releasing memory in Detector" << std::endl;
}

// Getters and setters
std::string Detector::type() const { return type_; }
bool Detector::is_on() const { return is_on_; }
int Detector::counts() const {
  if (!is_on_) {
    throw std::runtime_error("Device is off");
  }
  return counts_;
}

void Detector::On() { is_on_ = true; }
void Detector::Off() { is_on_ = false; }
void Detector::set_type(const std::string &type) {
  const bool available =
    std::find(available_detectors_.begin(), available_detectors_.end(), type) != available_detectors_.end();
    // std::ranges::find(available_detectors_, type) != available_detectors_.end();
  if (!available) {
    throw std::invalid_argument("Detector type is not available");
  }
  type_ = type;
}

// Other methods
void Detector::Detect(const Source &source) {
  // Device power status check
  if (!is_on_) {
    throw std::runtime_error("Device is off");
  }

  // Generate random integer between 0 and 1000
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(0, 1000);

  counts_ = dist(gen);
}
} // namespace detector