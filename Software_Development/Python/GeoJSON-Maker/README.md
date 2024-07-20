# CSV to GeoJSON Converter


This Python script converts geocoded location data from a CSV file into GeoJSON format, enabling its use in various GIS applications and mapping tools.

The primary purpose of this script is to facilitate the conversion of collected location data into latitude and longitude coordinates for integration into a website I developed.
This website, [Diamond Table Finder](https://www.diamondtablefinder.com), is designed to assist billiard players in locating venues equipped with a specific brand of premium pool tables. 
It serves as a valuable resource for dedicated players who are visiting new areas and wish to play on high-quality equipment.

## Requirements

- Python 3.x
- `csv` module (included with Python)
- `json` module (included with Python)

## Usage

1. Place the input CSV file (in this case: `geocoded-dtf-locations.csv`) in the same directory as the script.

2. Run the script:
   ```sh
   python csv_to_geojson.py
