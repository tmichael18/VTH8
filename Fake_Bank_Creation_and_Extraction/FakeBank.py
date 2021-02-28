import pandas as pd
import requests
import json

apiKey = "INPUT API KEY HERE"

# Adds a customer
def addCustomers(x):
    # x is a vector for each row
    customer = {
        "first_name": x["first_name"],
        "last_name": x["last_name"],
        "address": {
            "street_number": str(x["street_number"]),
            "street_name": x["street_address"],
            "city": x["city"],
            "state": x["state"],
            "zip": str(x["zip_code"])
        }
    }

    url = "http://api.nessieisreal.com/customers?key={}".format(apiKey)
    response = requests.post(
        url,
        data=json.dumps(customer),
        headers={'content-type': 'application/json'}
    )
    return response.json()

# Return a list of current customers within the API
def showCustomers():
    response = requests.get(
        url="http://api.nessieisreal.com/customers?key={}".format(apiKey),
        headers={'content-type': 'application/json'}
    )
    # response.json is a list of jsons for each customer
    return response.json()

# Delete customers made while testing
def deleteCustomers():
    response = requests.delete(
        url="http://api.nessieisreal.com/data?type=Customers&key={}".format(apiKey),
        headers={'content-type': 'application/json'}
    )
    return

# Adds an account given a row
def addAccounts(row):
    payload = {
        "type": "Savings",
        "nickname": row["first_name"] + " " + row["last_name"] + "'s savings account",
        "rewards": 0,
        "balance": int(row["initial_balance"])
    }
    response = requests.post(
        url="http://api.nessieisreal.com/customers/{}/accounts?key={}".format(row["customer_id"], apiKey),
        data=json.dumps(payload),
        headers={'content-type': 'application/json'}
    )
    return response.json()

# Helper to delete accounts created while testing
def deleteAccounts():
    response = requests.delete(
        url="http://api.nessieisreal.com/data?type=Accounts&key={}".format(apiKey),
        headers={'content-type': 'application/json'}
    )
    return

# Used to complete the operations for each row
def overallOperations(x, purchase_id, loan_id):
    # x is the entire row as a Series
    for i in range(12):
        monthOperation(x, i + 1, purchase_id, loan_id)
    return

# Used to create 3 columns for each month
def monthOperation(row, month, purchase_id, loan_id):
    deposit = row["deposit_" + str(month)]
    loan = row["loans_" + str(month)]
    purchase = row["purchases_" + str(month)]
    depositOperation(deposit, row, month)
    purchaseOperation(purchase, row, purchase_id, "Purchase" + str(month))
    purchaseOperation(loan, row, loan_id, "Loan" + str(month))
    return

# Used to make a deposit (summed for the total and made at the start of every month)
def depositOperation(depositAmount, row, description):
    payload = {
        "medium": "balance",
        "amount": depositAmount,
        "description": str(description)
    }
    response = requests.post(
        url="http://api.nessieisreal.com/accounts/{}/deposits?key={}".format(row["account_id"], apiKey),
        data=json.dumps(payload),
        headers={'content-type': 'application/json'}
    )
    return

# Used to create payments (either monthly payments for loans, or for general purchases of that month)
def purchaseOperation(purchaseAmount, row, merchantID, description):
    payload = {
        "merchant_id": merchantID,
        "medium": "balance",
        "amount": purchaseAmount,
        "description": description
    }
    response = requests.post(
        url="http://api.nessieisreal.com/accounts/{}/purchases?key={}".format(row["account_id"], apiKey),
        data=json.dumps(payload),
        headers={'content-type': 'application/json'}
    )
    return

# Used for ease of access to object id
def extractID(x):
    return (x["objectCreated"])["_id"]

# This creates merchants to allow our customers to make purchases
def createMerchants():
    # Request for the general Purchases
    payload = {
        "name": "Purchases",
        "address": {
            "street_number": "1234",
            "street_name": "Prices Fork Rd",
            "city": "Blacksburg",
            "state": "VA",
            "zip": "24060"
        },
        "geocode": {
            "lat": 0,
            "lng": 0
        }
    }
    response = requests.post(
        url="http://api.nessieisreal.com/merchants?key={}".format(apiKey),
        data=json.dumps(payload),
        headers={'content-type': 'application/json'}
    )
    purchase_id = extractID(response.json())

    # Request for the general Loans
    payload = {
        "name": "Loans",
        "address": {
            "street_number": "1235",
            "street_name": "Prices Fork Rd",
            "city": "Blacksburg",
            "state": "VA",
            "zip": "24060"
        },
        "geocode": {
            "lat": 0,
            "lng": 0
        }
    }
    response = requests.post(
        url="http://api.nessieisreal.com/merchants?key={}".format(apiKey),
        data=json.dumps(payload),
        headers={'content-type': 'application/json'}
    )
    loan_id = extractID(response.json())

    # Return the merchants' ids
    return purchase_id, loan_id


def main():

    # Read the data in:
    data = pd.read_csv("data10.csv")

    # First, create customers
    testing = data.apply(addCustomers, axis=1)
    data["customer_id"] = testing.apply(extractID)

    # Second, create accounts for each customer
    accounts = data.apply(addAccounts, axis=1)
    data["account_id"] = accounts.apply(extractID)

    # We have now created a customer and account for each person, and created 2 new columns to access that person's
    # account or customer
    # Before we do this, we need to create 2 merchants: One for all purchases, and one for all loan payments
    purchase_id, loan_id = createMerchants()

    # For each customer, for each month, create 1 deposit and 2 purchases (purchases and loans)
    data.apply(overallOperations, axis=1, purchase_id=purchase_id, loan_id=loan_id)

    # Bank creation is complete
    return


# Used to run the program
if __name__ == '__main__':
    main()