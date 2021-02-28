import pandas as pd
import requests
import string

apiKey = "INSERT API KEY HERE"

# Pulls all account data relating to the account_id and appends it to the Dataframe
def pullAccountData(accountID, df):
    data = dict()
    data = getDepositData(accountID, data)
    data = getLoansAndPurchasesData(accountID, data)
    currentBalance = retrieveCurrentBalance(accountID)
    calculateInitialBalance(data, currentBalance)
    return df.append(data, ignore_index=True)

# Retrieves the current balance as of right now
def retrieveCurrentBalance(accountID):
    response = requests.get(
        url="http://api.nessieisreal.com/accounts/{}?key={}".format(accountID, apiKey),
        headers={'content-type': 'application/json'}
    )
    return (response.json())["balance"]

# Calculate how much money the account had 12 months prior
def calculateInitialBalance(data, currentBalance):
    for i in data.keys():
        if ("deposit" in i):
            currentBalance -= data[i]
        else:
            currentBalance += data[i]
    data["initial_balance"] = currentBalance
    return data

# Retrieves all deposits made in the last year and records it
def getDepositData(accountID, data):
    response = requests.get(
        url="http://api.nessieisreal.com/accounts/{}/deposits?key={}".format(accountID, apiKey),
        headers={'content-type': 'application/json'}
    )
    for i in response.json():
        data["deposit_" + str(i["description"])] = i["amount"]
    return data

# Retrieves all payments made in the last year and records it
def getLoansAndPurchasesData(accountID, data):
    response = requests.get(
        url="http://api.nessieisreal.com/accounts/{}/purchases?key={}".format(accountID, apiKey),
        headers={'content-type': 'application/json'}
    )
    for i in response.json():
        if "Purchase" in i["description"]:
            data["purchases_" + i["description"].strip(string.ascii_letters)] = i["amount"]
        else:
            data["loans_" + i["description"].strip(string.ascii_letters)] = i["amount"]
    return data


def main():
    # Pulling from the bank:
    # Pull customers and put it into a seperate dataframe
    # Make 12 dataframes, 1 for each month
    # For each month's dataframe, we are adding data for the deposit, purchase, and loans
    # For each month, we are imputing the balance for that month with those values, working backwards
    # Finally, we impute the initial income at the beginning of the year
    # And we concat all the dataframes together in order
    df = pd.DataFrame()
    response = requests.get(
        url="http://api.nessieisreal.com/accounts?key={}".format(apiKey),
        headers={'content-type': 'application/json'}
    )
    for i in response.json():
        df = pullAccountData(i["_id"], df)
    df.to_csv("Zaid's NEW data.csv")

# Used to run the program
if __name__ == '__main__':
    main()
