#ifndef ASSIGNMENT_3_GDETECTOR_H
#define ASSIGNMENT_3_GDETECTOR_H

#include <ctime>
#include <string>
#include <vector>

/**
 * @class Source
 * @class Detector
 */

namespace detector {
/**
 * @class Source
 * @brief Represents a radioactive source with specific characteristics,
 * including name, acquisition date, activity, and unique identifier.
 *
 * We reckon in this demo code user should not specify or modify ID for the
 * source. This is handled by UUID v4 to guarantee uniqueness.
 *
 * @details
 * - The name of the source could represent common isotopes such as Na-22,
 * Cs-136, or Co-92.
 * - The activity represents the radioactivity of the source expressed in
 * Becquerels per kilogram (Bq/kg).
 * - The unique ID is automatically generated in UUID4 format.
 */
class Source {
 private:
  std::string name_{};  // Source name. e.g. Na-22, Cs-136, Co-92
  time_t date_{};       // Date of source acquisition
  double activity_{};   // Source activity at the time of acquisition (Bq/kg)
  std::string id_{};    // Unique ID of the source

  static std::vector<std::string> available_sources_;

 public:
  // Constructor and destructors
  explicit Source();
  explicit Source(const std::string& name, const time_t& date,
                  const double& activity);
  ~Source();

  // Getters and setters
  [[nodiscard]] std::string name() const;
  [[nodiscard]] time_t date() const;
  [[nodiscard]] double activity() const;
  [[nodiscard]] std::string id() const;
  [[nodiscard]] static std::vector<std::string> available_sources();

  void set_name(const std::string& name);
  void set_date(const time_t& date);
  void set_activity(const double& activity);
  static void set_available_sources(const std::vector<std::string>& sources);

  // Printers
  friend std::ostream& operator<<(std::ostream& os, const Source& source);
};
/**
 * @class Detector
 * @brief
 */
class Detector {
 private:
  std::string type_{};
  bool is_on_ = false;
  int counts_{};
 static std::vector<std::string> available_detectors_;

 public:
  // Constructors and destructors
  explicit Detector() = default;
  explicit Detector(const std::string& type);
  ~Detector();

  // Getters and setters
  [[nodiscard]] std::string type() const;
  [[nodiscard]] bool is_on() const;
  [[nodiscard]] int counts() const;

  void On();
  void Off();
  void set_type(const std::string& type);

  // Other methods
  void Detect(const Source& source);
};

}  // namespace detector

#endif  // ASSIGNMENT_3_GDETECTOR_H
