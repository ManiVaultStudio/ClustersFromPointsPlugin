# Clusters from points plugin
![Screenshot of the clusters from points plugin user interface](res/images/screenshot.png)

This analysis plugin is used to derive clusters from points using various extraction algorithms. 

```
git clone git@github.com:ManiVaultStudio/ClustersFromPointsPlugin.git
```

Points are grouped (clustered) based on their numerical value for a user specified dimension. Point values can be grouped by:
  - their rounded numerical value (Identifier)
  - their point index (Index)
  - in which interval they fall (Stratification)
  - a user defined interval (Interval)

## Usage
Please follow these steps to generate clusters:
- Right-click a points dataset in the data hierarchy
- Choose Analyze > `Extract clusters`
- Pick a grouping algorithm
- Click `Start`

To start, you can also select one or multiple cluster datasets with this analysis and click Analyze > `Start clustering...`
