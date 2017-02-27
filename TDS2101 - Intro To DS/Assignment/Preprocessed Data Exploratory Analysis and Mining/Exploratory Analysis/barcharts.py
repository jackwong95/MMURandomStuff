import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

us_state_abbrev = {
    'Alabama': 'AL',
    'Alaska': 'AK',
    'Arizona': 'AZ',
    'Arkansas': 'AR',
    'California': 'CA',
    'Colorado': 'CO',
    'Connecticut': 'CT',
    'Delaware': 'DE',
    'Florida': 'FL',
    'Georgia': 'GA',
    'Hawaii': 'HI',
    'Idaho': 'ID',
    'Illinois': 'IL',
    'Indiana': 'IN',
    'Iowa': 'IA',
    'Kansas': 'KS',
    'Kentucky': 'KY',
    'Louisiana': 'LA',
    'Maine': 'ME',
    'Maryland': 'MD',
    'Massachusetts': 'MA',
    'Michigan': 'MI',
    'Minnesota': 'MN',
    'Mississippi': 'MS',
    'Missouri': 'MO',
    'Montana': 'MT',
    'Nebraska': 'NE',
    'Nevada': 'NV',
    'New Hampshire': 'NH',
    'New Jersey': 'NJ',
    'New Mexico': 'NM',
    'New York': 'NY',
    'North Carolina': 'NC',
    'North Dakota': 'ND',
    'Ohio': 'OH',
    'Oklahoma': 'OK',
    'Oregon': 'OR',
    'Pennsylvania': 'PA',
    'Rhode Island': 'RI',
    'South Carolina': 'SC',
    'South Dakota': 'SD',
    'Tennessee': 'TN',
    'Texas': 'TX',
    'Utah': 'UT',
    'Vermont': 'VT',
    'Virginia': 'VA',
    'District Of Columbia': 'WA',
    'West Virginia': 'WV',
    'Wisconsin': 'WI',
    'Wyoming': 'WY',
    'Country Of Mexico': 'MX',
}
    
# Plotting style.
plt.style.use('ggplot')

# Read preprocessed data.
data = pd.read_csv("../6-cols.csv")
del data['Unnamed: 0']

# Abbrev
state = []
states = data["State"]
for temp in states:
    state.append(us_state_abbrev[temp])
    
data["State"] = pd.Series(state,  index = data.index)

# Means
CO_means = data.groupby(["State"])["CO AQI"].mean()
SO2_means = data.groupby(["State"])["SO2 AQI"].mean()
O3_means = data.groupby(["State"])["O3 AQI"].mean()
NO2_means = data.groupby(["State"])["NO2 AQI"].mean()

# Labels for plots
labels = np.unique(data["State"])
y_pos = np.arange(len(labels))

plt.figure("CO", figsize=(15,15))
plt.bar(y_pos, CO_means, align='center', alpha=0.5)
plt.title('Bar Chart for Carbon Monoxide')
plt.xticks(y_pos, labels)
plt.axhline(y = 10.3, color = 'r', linestyle = '-')
plt.tight_layout()
# plt.show()
plt.savefig('Images/Carbon Monoxide distribution.png')

plt.figure("SO2", figsize=(15,15))
plt.bar(y_pos, SO2_means, align='center', alpha=0.5)
plt.title('Bar Chart for Sulphur Dioxide')
plt.xticks(y_pos, labels)
plt.axhline(y = 20.2, color = 'r', linestyle = '-')
plt.tight_layout()
# plt.show()
plt.savefig('Images/Sulphur Dioxide distribution.png')

plt.figure("O3", figsize=(15,15))
plt.bar(y_pos, O3_means, align='center', alpha=0.5)
plt.title('Bar Chart for Ozone')
plt.xticks(y_pos, labels)
plt.axhline(y = 44.4, color = 'r', linestyle = '-')
plt.tight_layout()
# plt.show()
plt.savefig('Images/Ozone distribution.png')

plt.figure("NO2", figsize=(15,15))
plt.bar(y_pos, NO2_means, align='center', alpha=0.5)
plt.title('Bar Chart for Nitrogen Dioxide')
plt.xticks(y_pos, labels)
plt.axhline(y = 35, color = 'r', linestyle = '-')
plt.tight_layout()
# plt.show()
plt.savefig('Images/Nitrogen Dioxide distribution.png')

