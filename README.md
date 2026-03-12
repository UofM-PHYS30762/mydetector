# Library for assignment 3: `gdetector`

This library is a demo library for assignment 3.
The core features are a `Source` and a `Detector` class.

They have the following properties:

##### `Source`

- `name`: the name of the source must be one of `available_sources`
- `date`: acquisition date
- `activity`: activity of the source in Bq/kg
- `id`: unique identifier
- static attribute `available_sources`: a list of available sources, default to
  `["Na-22", "Cs-136", "Co-92"]`

##### `Detector`

- `type`: type of the detector, must be one of `available_detectors_`
- `is_on`: `bool`, the state of the detector
- `count`: The detected radioactive activity.
- static attribute `available_detectors_`: a list of available detectors, default to
  `["Scintillator", "Geiger", "Germanium"]`
- `On()` and `Off()`: Methods to turn on and off the detector
- `Detect(&source)`: Method to detect the activity of a given source

> [!NOTE]
> The detector must be turned on before it can detect the activity of a source.

## Basic usage
### `Source`
```c++
#include <iostream>
#include <gdetector/gdetector.h>
int main() {
  std::cout << "=== Source Demo === \n";
  // === Instantiate a Source ===
  // Use default constructor
  detector::Source source1;
  source1.set_name("Na-22");
  source1.set_date(time(nullptr));
  source1.set_activity(98.7899);
  
  // Use constructor with arguments
  detector::Source source2("Cs-136", time(nullptr), 12.3456);
  
  // === Access attributes ===
  std::cout << source1.name() << "\n";
  std::cout << source2.activity() << "\n";
  std::cout << source2.id() << "\n";
  std::cout << source2.date() << "\n";
  
  // === Print source ===
  std::cout << source1 << "\n";
  std::cout << source2 << "\n";
  
  // === Modify available sources ===
  std::vector<std::string> alternative_sources = {"Pu-268", "Am-234"};
  detector::Source::set_available_sources(alternative_sources);
  source1.set_name("Pu-268");
  // Revert to default to avoid corruption
  detector::Source::set_available_sources({"Na-22", "Cs-136", "Co-92"});
}
```

### `Detector`
```c++
std::cout << "=== Detector Demo === \n";
detector::Detector detector;
detector.set_type("Geiger");
detector.On();

time_t timestamp1;
time(&timestamp1);
detector::Source source("Cs-136", timestamp1, 123.456);
detector.Detect(source);
std::cout << "Detected " <<detector.counts() << std::endl;
```
## Add `gdetector` to your project

```bash
git submodule add --depth 1 https://github.com/UofM-PHYS30762/mydetector.git mydetector
```
