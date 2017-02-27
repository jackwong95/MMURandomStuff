import pandas as pd
import numpy as np
import os.path
import datetime as dt
import matplotlib.cm as cmx
import matplotlib.colors as colors
import matplotlib.pyplot as plt
import plotly.offline as offline
from matplotlib import style

# Global variables

outputDirPrefix = "../Plots/"
outputDirExtras = outputDirPrefix + "Extras/"
outputDirMonthsYearEachState = outputDirPrefix + "Months Year Each State/"
outputDirMonthsEachYear = outputDirPrefix + "Months Each Years/"
outputDirChoropleth = outputDirPrefix + "Plotly's HTML Choropleth/"
outputDirTop3State = outputDirExtras + "Top 3 State/"

datasetNameTrain = "../Dataset/clean_and_relevant_training.csv"
datasetNameTest = "../Dataset/clean_and_relevant_testing.csv"

pollutant_type = ["CO", "NO2", "O3", "SO2"]

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
}

for path in [outputDirPrefix, outputDirExtras, outputDirMonthsYearEachState, outputDirMonthsEachYear,
             outputDirChoropleth, outputDirTop3State, outputDirChoropleth+"CO", outputDirChoropleth+"NO2",
             outputDirChoropleth+"O3", outputDirChoropleth+"SO2"]:
    if not os.path.exists(path):
        os.makedirs(path)
        
# Date loading and pre-processing
# if the pre processed file does not exist
if not os.path.isfile(datasetNameTrain):
    # if preprocessed data does not exist pre process the raw data set
    complete = pd.read_csv("../Dataset/pollution_us.csv", index_col = 0)
    
    # slice dataset by half
    training = complete.iloc[0:int(len(complete)/2), :]
    testing = complete.iloc[int(len(complete)/2):, :]
    
    # Impute the NA values
    coAQITrain = training["CO AQI"]
    coAQITrain.fillna(method='bfill', inplace=True)
    so2AQITrain = training["SO2 AQI"]
    so2AQITrain.fillna(method='ffill', inplace=True)

    # Apply the imputed values
    training["CO AQI"] = coAQITrain
    training["SO2 AQI"] = so2AQITrain

    # Convert to date time object add 2 new columns called Year and Month
    year_months = []
    years = []
    dateLoc = training["Date Local"]
    for date in dateLoc:
        temp = dt.datetime.strptime(date, "%Y-%m-%d")

        if (temp.month < 10):
            month = "0" + str(temp.month)
        else:
            month = str(temp.month)
        year_months.append(str(temp.year) + "-" + month)
        years.append(str(temp.year))

    training["Year Month"] = pd.Series(year_months,  index = training.index)
    training["Year"] = pd.Series(years,  index = training.index)
    training = training.drop_duplicates()
    training.to_csv(datasetNameTrain, index = True, mode = "w")
    
    # Impute the NA values
    coAQITrain = testing["CO AQI"]
    coAQITrain.fillna(method='bfill', inplace=True)
    so2AQITrain = testing["SO2 AQI"]
    so2AQITrain.fillna(method='ffill', inplace=True)

    testing["CO AQI"] = coAQITrain
    testing["SO2 AQI"] = so2AQITrain
    dateLoc = testing["Date Local"]
    # Convert to date time object add 2 new columns called Year and Month
    year_months = []
    years = []

    for date in dateLoc:
        temp = dt.datetime.strptime(date, "%Y-%m-%d")

        if (temp.month < 10):
            month = "0" + str(temp.month)
        else:
            month = str(temp.month)
        year_months.append(str(temp.year) + "-" + month)
        years.append(str(temp.year))

    testing["Year Month"] = pd.Series(year_months,  index = testing.index)
    testing["Year"] = pd.Series(years,  index = testing.index)
    testing = testing.drop_duplicates()
    testing.to_csv(datasetNameTest, index = True, mode = "w")
    
    del testing
    del training
    
#convert the date local to panda's date time object
training = pd.read_csv(datasetNameTrain, index_col = 0)
training["Date Local"] = pd.to_datetime(training["Date Local"], format = "%Y-%m-%d")

# re defining years
years = [2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009]

# Exploratory analysis
'''
#get a better feel of the dataset
print(complete.drop_duplicates())
print(complete.shape[0] - complete.drop_duplicates().shape[0])
print(complete.isnull().sum())
print(complete.describe())
print(complete.head())
print(complete.tail())
print(complete.dtypes)
print(complete.shape)
#making sure that all observations are sorted by date
#in case if i subset it wrongly. 
print((complete["Date Local"].sort - complete["Date Local"]).unique())
'''

# Exploratory plots

# Sum for each pollution plot
pollutant_list = []

# Get all attributes needed
for pollutant in pollutant_type:
    # normalize data
    if training[pollutant+" Units"].unique()[0] == "Parts per million":
        temp = training[pollutant+" Mean"].sum() / 1000
    else:
        temp = training[pollutant+" Mean"].sum()
    pollutant_list.extend([{"pollutant.type":pollutant, "pollutant.measurement":"billion", "pollutant.sum":temp}])

# Make it into a pandas df
pollutant_sum_df =  pd.DataFrame(pollutant_list)

style.use('ggplot')

ax = pollutant_sum_df[["pollutant.type","pollutant.sum"]].plot(kind='bar', title ="Pollution summation", figsize=(15, 10), legend = False, fontsize=12)
ax.set_xlabel("Pollution Type", fontsize=12)
ax.set_ylabel("Billion", fontsize=12)

plt.title("Pollution summation")
plt.xticks(range(len(pollutant_sum_df)), pollutant_sum_df[["pollutant.type"]].values.flatten())
plt.savefig(outputDirExtras + "summation of each pollutant")

plt.show()

# Average pollution over the years plot

pollutant_list = []

for pollutant in pollutant_type:
    
    subset = training[["Date Local", pollutant + " Mean"]]
    
    for year in training["Year"].unique():
        pollutant_list.extend([{"pollution.type":pollutant, "year":year, "pollution.mean":training[training["Date Local"].dt.year == year][pollutant+" Mean"].mean(), "pollutant.measurement":training[pollutant+" Units"].unique()[0]}])
        
pollutant_mean_df =  pd.DataFrame(pollutant_list)

fig, ax = plt.subplots(1,1)
pollutant_mean_df.groupby("pollution.type").plot(x="year", y="pollution.mean", ax = ax)
ax.ticklabel_format(useOffset = False)
ax.legend(labels=['CO', 'NO2', 'O3', 'SO2'])
ax.set_ylabel("Billion")
ax.set_xlabel("Year")

plt.title("Pollution mean over years")
plt.savefig(outputDirExtras + "pollution mean")
plt.show()

# Normalized of each pollution across the years plot
pollutant_list = []
pollutant_list2 = []

avg = np.zeros(len(years))

for pollutant in pollutant_type:
    
    mean = np.array([])
    
    for year in years:
        mean = np.append(mean, training[training["Date Local"].dt.year == year][pollutant+" Mean"].mean())
    
    maxVal = mean.max()
    minVal = mean.min()
    
    norm = np.array([])
    for temp in mean:
        norm = np.append(norm, (temp - minVal) / (maxVal - minVal))
        
    avg = avg + norm

    for idx in range(len(years)):
        pollutant_list.extend([{"pollution.type":pollutant, "year":years[idx], "normalized.pollution":norm[idx]}])

pollutant_norm_df =  pd.DataFrame(pollutant_list)
        
fig, ax = plt.subplots(1,1)
pollutant_norm_df.groupby("pollution.type").plot(x="year", y="normalized.pollution", ax = ax)
ax.ticklabel_format(useOffset = False)
ax.legend(labels=['CO', 'NO2', 'O3', 'SO2'], prop = {"size":7}, loc = "upper right")
ax.set_ylabel("Normalized")
ax.set_xlabel("Year")

plt.title("Pollution mean normalized over years")
plt.savefig(outputDirExtras + "normalize pollutant over the years")
plt.show()

plt.clf()

# Generalized pollution distribution across the years plot
avg = avg / len(pollutant_type)

for idx in range(len(years)):
    pollutant_list2.extend([{"year":years[idx], "generalized.pollution":avg[idx]}])

pollutant_gen_df =  pd.DataFrame(pollutant_list2)    
    
fig, ax = plt.subplots(1,1)
pollutant_gen_df.plot(x="year", y="generalized.pollution", ax = ax)
ax.ticklabel_format(useOffset = False)
ax.legend_.remove()
ax.set_ylabel("Normalized")
ax.set_xlabel("Year")

plt.title("Generalized and normalized pollution over years")
plt.savefig(outputDirExtras + "generalized pollution")
plt.show()

plt.clf()

# Generalized and summation of pollution for each state
stateNormPollution = {}
for state in training["State"].unique():
    
    subsetState = training[training["State"] == state]
        
    pollutionToArray = {}
    for pollutant in pollutant_type:
        
        subset = subsetState[["Date Local", pollutant + " Mean"]]
        
        average = np.array([])
        
        for year in years:
            average = np.append(average, subset[subset["Date Local"].dt.year == year][pollutant+" Mean"].mean())
        
        nanIdx = np.where(np.isnan(average))
        nonNanIdx = np.isfinite(average)
        imputeVal = average[nonNanIdx].mean()
        if imputeVal is np.nan:
            imputeVal = 0
            
        average[nanIdx] = imputeVal
        pollutionToArray[pollutant] = average
        
    avgTemp = np.zeros(len(years))    
    
    for keys in pollutionToArray.keys():
        
        average = pollutionToArray[keys]
        
        maxVal = average.max()
        minVal = average.min()
        temp = np.array([])
        for avg in average:
            try:
                temp = np.append(temp, float(avg - minVal) / float(maxVal - minVal))
            except ZeroDivisionError:
                temp = np.append(temp, np.nan) 
        avgTemp = avgTemp + temp
        
        temp = avgTemp.mean() / len(pollutionToArray.keys())
        if ~np.isnan(temp).any():
            stateNormPollution[state] = temp 
            
from operator import itemgetter
sortedDict = sorted(stateNormPollution.items(), key=itemgetter(1), reverse = True)

pollutant_list = []

for state, norm_pollutant in sortedDict:
    pollutant_list.extend([{"state":state, "generalized.pollutant":norm_pollutant}])
    
generalized_norm_df =  pd.DataFrame(pollutant_list)

ax = generalized_norm_df[["state","generalized.pollutant"]].plot(kind='bar', title ="Pollution contribution sorted by state", figsize=(15, 10), legend = False, fontsize=12)
ax.set_xlabel("State", fontsize=12)
ax.set_ylabel("Normalized", fontsize=12)

plt.subplots_adjust(bottom=0.29)
plt.title("Pollution generalized by state")
plt.xticks(range(len(generalized_norm_df)), generalized_norm_df[["state"]].values.flatten())
plt.savefig(outputDirExtras + "pollution contribution by state")
plt.show()

# top 3 state contribution for each type of pollutant
# generate colors
def get_cmap(N):
    '''Returns a function that maps each index in 0, 1, ... N-1 to a distinct 
    RGB color.'''
    color_norm  = colors.Normalize(vmin=0, vmax=N-1)
    scalar_map = cmx.ScalarMappable(norm=color_norm, cmap='brg') 
    def map_index_to_rgb_color(index):
        return scalar_map.to_rgba(index)
    return map_index_to_rgb_color

pollutant_list = []

for state in training["State"].unique():
    for year in years:    
        subset = training[(training["State"]  == state) & (training["Date Local"].dt.year == year)]
        pollutant_list.extend([{"state":state, "year":year, "CO.mean":(subset[["CO Mean"]].mean()[0]/1000), "SO2.mean":subset[["SO2 Mean"]].mean()[0], "O3.mean":(subset[["O3 Mean"]].mean()[0]/1000), "NO2.mean":subset[["NO2 Mean"]].mean()[0]}])
         
total_pollution_df =  pd.DataFrame(pollutant_list)

pollutant_list = []

# Take only the top 3 states for each type of pollution of each year
for year in years:
    sub = total_pollution_df[total_pollution_df["year"] == year]
    for pollutant in pollutant_type:    
        top = sub.sort_values([pollutant+".mean"], ascending=[0]).iloc[0:3,:]
        top = top[["year", "state", pollutant+".mean"]]
        top.rename(columns={"year":"year", "state":"state", pollutant+".mean":"pollution.mean"}, inplace = True)
        top["pollution.type"] = pollutant
        top["ranking"] = pd.Series(range(0, 3), index = top.index)
        pollutant_list.extend(top.to_dict(orient = "records"))


selected_state_year =  pd.DataFrame(pollutant_list)

ind = np.arange(len(selected_state_year["year"].unique())) # the x locations for the groups
width = 0.3       # the width of the bars
# for color mapping for each state to the color of bar
cmap = get_cmap(len(selected_state_year["state"].unique()))
state_to_col = {}
for idx, state in enumerate(selected_state_year["state"].unique()):
    state_to_col[state] = cmap(idx)

plt.clf()

for pollutant in selected_state_year["pollution.type"].unique():
    # plot  
    plt.figure(figsize=(20,20))
    fig = plt.figure()
    ax = fig.add_subplot(111)
    # has labelled? to avoid duplicate labels.
    has_label_flag = []
    
    for rank in selected_state_year["ranking"].unique():
    
        subset = selected_state_year[(selected_state_year["pollution.type"] == pollutant) & (selected_state_year["ranking"] == rank)]
        
        for state in subset["state"].unique():
            a1 = np.array(subset[["state"]] == state).flatten()
            a2 = np.array(subset[["pollution.mean"]]).flatten()
            final = a1*a2    
            if state not in has_label_flag:    
                ax.bar(ind, final, width, color = state_to_col[state], label = state)
                has_label_flag.extend([state])
            else:
                ax.bar(ind, final, width, color = state_to_col[state])
        ind = ind + width
        
    ax.set_ylabel("Billion")
    ax.set_xlabel("Years")
    ax.set_title("Top 3 state total " + pollutant)
    ax.set_xticks(ind-width)
    ax.set_xticklabels(np.unique(selected_state_year["year"]))
    
    plt.tight_layout()
    plt.legend(prop={'size':7}, loc = "upper right")
    plt.savefig(outputDirTop3State  + pollutant)

plt.show()


'''
Generate pollutants for each state across month and years
'''
subset = training[["Year Month", "State", "CO Mean", "SO2 Mean", "O3 Mean", "NO2 Mean"]]

for pollutant in pollutant_type:

    plt.figure(figsize=(15,15))
    
    lab = []
    
    for state in training["State"].unique():
        subsubset = subset[subset["State"] == state]
        aggregated = subsubset.groupby(["Year Month"], as_index = False).mean()
        agdx = [dt.datetime.strptime(d,'%Y-%m').date() for d in aggregated["Year Month"]]
        
        plt.plot(agdx, aggregated[pollutant + " Mean"])
        lab.append(state)
    
    plt.xlabel("Year Month")
    plt.ylabel("Per Billion")
    plt.legend(labels = lab, prop = {"size":10}, loc = "upper right")
    plt.title(pollutant + " Mean distribution across the years and months for each state")
    plt.savefig(outputDirMonthsYearEachState + pollutant)
plt.show()

'''
Pollutant trend for each pollutant throughout the months for each year
'''
subset = training[["Year Month", "Year", "State", "CO Mean", "SO2 Mean", "O3 Mean", "NO2 Mean"]]

temp = pd.Series(subset["Year Month"]).values
months = []

for val in temp:
    months.append(str(val[5:7]))

subset["Month"] = pd.Series(months,  index = training.index)

tempList = []

for year in training["Year"].unique():
    subsubset = subset[subset["Year"] == year]
    
    aggregated = subsubset.groupby(["Month"], as_index = False).mean()
    tempList.append(aggregated)
    
for pollutant in pollutant_type:
    
    lab = []
    plt.figure(figsize=(15,15))
    
    for dat in tempList:
        
        plt.plot(dat["Month"], dat[pollutant + " Mean"])
        lab.append(dat["Year"].unique())
    
    plt.xlabel("Month")
    plt.ylabel("Billion")
    plt.legend(labels = lab, prop = {"size":10}, loc = "upper right")
    plt.title(pollutant + " Mean distribution across the years and months for each state")
    plt.savefig(outputDirMonthsEachYear+pollutant)
    plt.show()


'''
choropleth plot 
'''
dataOfinterest = training[["Year", "State", "CO AQI", "SO2 AQI", "O3 AQI", "NO2 AQI"]]

yearToState = {}
# Synchornize all of the z axis to unified value, so we can see the same color
# Representing the same information
pollutionToZMax={"SO2":40, "O3":65, "NO2":50, "CO":20}

df = None

for year in dataOfinterest["Year"].unique():
    for state in dataOfinterest["State"].unique():
        
        if state == "Country Of Mexico":
            continue
        
        temp = dataOfinterest[(dataOfinterest["State"] == state) & (dataOfinterest["Year"] == year)]
        aggregated = temp.groupby(["Year"], as_index = False).mean()
        aggregated["state"] = state
        aggregated["code"] = us_state_abbrev[state]
        
        if df is None:
            df = aggregated
        else:
            df = df.append(aggregated)
            
    df.index = range(len(df))
    yearToState[str(year)] = df
    df = None

for pollutant in pollutant_type:
    
    for key, df in yearToState.items():
        
        for col in df.columns:
            df[col] = df[col].astype(str)
        
        scl = [[0.0, 'rgb(242,240,247)'],[0.2, 'rgb(218,218,235)']
               ,[0.4, 'rgb(188,189,220)'],[0.6, 'rgb(158,154,200)'],
               [0.8, 'rgb(117,107,177)'],[1.0, 'rgb(84,39,143)']]
        
        df['text'] = df["state"]
        
        data = [ dict(
                type='choropleth',
                colorscale = scl,
                autocolorscale = False,
                locations = df["code"],
                zmax = pollutionToZMax[pollutant],
                zmin = 0,
                z = df[pollutant + " AQI"].astype(float),
                locationmode = 'USA-states',
                text = df['text'],
                marker = dict(
                    line = dict (
                        color = 'rgb(255,255,255)',
                        width = 2
                    ) ),
                colorbar = dict(
                    title = "Air Quality Index")
                ) ]
        
        title = key + r" AQI distribution across the USA States of " +  pollutant + r" AQI"

        layout = dict(
                title = title,
                geo = dict(
                    scope='usa',
                    projection=dict( type='albers usa' ),
                    showlakes = True,
                    lakecolor = 'rgb(255, 255, 255)'),
                     )
                
        fig = dict( data=data, layout=layout)
        offline.plot(fig, filename = outputDirChoropleth+pollutant+"/"+key+".html",auto_open=False)