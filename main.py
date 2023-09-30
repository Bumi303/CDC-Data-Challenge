# Pandas is used for data manipulation
import pandas as pd
import csv
from datetime import datetime, timedelta

def convert_date(date_str):
    # Define a dictionary to map month abbreviations to their corresponding numerical values
    month_mapping = ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun',
        'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec']
        
    month_days = [0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 365]
    
    # Split the date string into day, month, and year components
    day, month, year = date_str.split('_')
    day = int(day[:-2])  # Convert '17th' to 17

    d_month = month_days[month_mapping.index(month)]
    year = int(year)
    
    if (year > 0 and year < 80):
        year = year + 100

    days_since = int(day) + int(d_month) + ((year - 80) * 365) 
    
    return days_since

def checkDup()

def main():
    features = pd.read_csv('GameData.csv')
    
    last_date = []
    release_date = []
    for i in range(1181):
        last_date.append(features.loc[i, "Last_Update_Real"])
        release_date.append(features.loc[i, "Release_Date"])
    

    with open('Clean_GameData.csv', mode='w') as f:
        days_since = []
        for i in range(len(last_date)):
            last_date[i] = convert_date(last_date[i])
            release_date[i] =  convert_date(release_date[i])
            days_since.append(last_date[i] - release_date[i])
            print(days_since[i], file=f)
    print(days_since)

main()
