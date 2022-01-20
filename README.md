# Clusters from points plugin
![Screenshot of the clusters from points plugin user interface](res/images/screenshot.png)
This analysis plugin is used to extract clusters from points using various extraction algorithms. Points are grouped (clustered) based on their numerical value for a user specified dimension. In its current state, the point values can be grouped by:
  - their rounded numerical value (Identifier)
  - in which interval they fall (Stratifaction)
  - a user defined interval (Interval)

## Usage
This plugin produces a clusters dataset and continuously updates the clusters as clustering parameters are changed. Please follow these steps to generate clusters:
- Right-click a points dataset in the data hierarchy
- Choose Analyze > Clusters from points
- Enter the name of the target clusters dataset
- Choose the extraction dimension
- Pick a grouping algorithm

# Building
### Requirements
* Git (https://git-scm.com/)
* CMake 3.12+ (https://cmake.org/)
* Qt 5.15.1 (https://www.qt.io/download)
* Visual Studio 2017+ (Windows https://visualstudio.microsoft.com/downloads/)
