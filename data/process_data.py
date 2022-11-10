import pandas as pd
import numpy as np
import geopy.distance
import csv

def distance(lat1, long1, lat2, long2): 
    point1= (lat1, long1)
    point2 = (lat2, long2)
    return geopy.distance.distance(point1, point2).miles

airports = pd.read_csv('data/airports.dat')
airports.drop(airports.columns[[2, 3, 4, 5, 8, 9, 10, 11, 12, 13]], axis=1, inplace=True) 
airports.dropna(inplace=True) 
airports = airports[
      (airports.airportid != '\\N') 
    & (airports.airportname != '\\N') 
    & (airports.latitude != '\\N') 
    & (airports.longitude != '\\N') 
    & (airports.latitude >= 24.520833)  #Latitude and longitude ranges taken from northernmost, southernmost, easternmost and westernmost places 
    & (airports.latitude <= 49.384472)  #Only considering contiguous states, so excluding Hawaii and Alaska
    & (airports.longitude >= -124.771694) 
    & (airports.longitude <= -66.947028)
    ]

airports = airports.to_numpy()
airport_information = {}
for row in airports:
    airport_information[row[0]] = [row[1], row[2], row[3]]

routes = pd.read_csv('data/routes.dat')
routes.drop(routes.columns[[0, 1, 2, 4, 6, 7, 8]], axis=1, inplace=True)
routes.dropna(inplace=True)
routes = routes[(routes.sourceairportid != '\\N') & (routes.destinationairportid != '\\N')]
routes = routes.values.tolist()

routes_with_distance = []
for route in routes:
    sourceid = int(route[0])
    destinationid = int(route[1])
    if (sourceid in airport_information.keys() and destinationid in airport_information.keys() and len(route) == 2):
        route.append(distance(airport_information[sourceid][1], airport_information[sourceid][2], airport_information[destinationid][1], airport_information[destinationid][2]))
        routes_with_distance.append(route)

with open('US_routes.dat', 'w', newline='') as f:
    writer = csv.writer(f)
    writer.writerows(routes_with_distance)

with open('US_airports.dat', 'w', newline='') as f:
    writer = csv.writer(f)
    for key, value in airport_information.items():
        writer.writerow((key, value[0]))