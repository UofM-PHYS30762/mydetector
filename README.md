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

[!NOTE]
> The detector must be turned on before it can detect the activity of a source.

## Basic usage

```c++
#include <iostream>
#include <gdetector/gdetector.h>

// === Instantiate a Source ===
// Use default constructor

detector::Source source1;

source
```

## Add `gdetector` to your project

```bash
git submodule add --depth 1 https://github.com/UofM-PHYS30762/mydetector.git mydetector
```
