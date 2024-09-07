import pandas as pd
hour = pd.read_csv('hour.csv')
print(hour.head())

print("\n\n Mean: \n", hour["count"].mean())
print("\n\n Median: \n", hour["count"].median())
print("\n\n Deviation of Count: \n", hour["count"].std())
print("\n\n Minimum registered: \n", hour["registered"].min())
print("\n\n Maximum registered: \n", hour["registered"].max())
