import csv
import json

# Define the input and output files
input_csv_file = 'geocoded-dtf-locations.csv'
output_geojson_file = 'geocoded-dtf-locations.geojson'

# Initialize an empty GeoJSON structure
geojson = {
    "type": "FeatureCollection",
    "features": []
}

# Open the CSV file for reading
with open(input_csv_file, mode='r', encoding='utf-8') as csv_file:
    csv_reader = csv.DictReader(csv_file)
    for row in csv_reader:
        # For each row in the CSV, create a GeoJSON feature
        feature = {
            "type": "Feature",
            "properties": {
                "Country": row["Country"],
                "State/Province": row["State/Province"],
                "City": row["City"],
                "Business Name": row["Business Name"],
                "Phone": row["Phone"],
                "Address": row["Address"],
                "Contact Name": row["Contact Name"],
                "Qty of 7ft Tables": row["Qty of 7ft Tables"],
                "Qty of 8ft Tables": row["Qty of 8ft Tables"],
                "Qty of 9ft Tables": row["Qty of 9ft Tables"],
                "Geocode Success": row["Geocode Success"]
            },
            "geometry": {
                "type": "Point",
                "coordinates": [float(row["Longitude"]), float(row["Latitude"])]
            }
        }
        # Add the feature to the GeoJSON structure
        geojson["features"].append(feature)

# Write the GeoJSON structure to an output file
with open(output_geojson_file, mode='w', encoding='utf-8') as geojson_file:
    json.dump(geojson, geojson_file, indent=2)

print(f"GeoJSON file '{output_geojson_file}' has been created.")