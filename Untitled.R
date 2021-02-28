# Reference code example for variable creation

income = c(10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000, 
           110000, 120000, 130000, 140000, 150000, 160000, 170000)

initbal = rep(0, 17)

for (i in 1:length(income)){
  if (income[i] <= 25000){
    initbal[i] = rnorm(1, 6021, 1000)
  }
  else if (income[i] <= 44999){
    initbal[i] = rnorm(1, 11719, 2000)
  }
  else if (income[i] <= 69999){
    initbal[i] = rnorm(1, 13179, 2000)
  }
  else if (income[i] <= 114999){
    initbal[i] = rnorm(1, 15333, 2000)
  }
  else if (income[i] <= 159999){
    initbal[i] = rnorm(1, 37645, 3000)
  }
  else {
    initbal[i] = rnorm(1, 117771, 10000)
  }
}





# Start looking at data, first few variables of personal info deleted first in excel
rm(list = ls())
setwd("~/Desktop")
bank_data = read.csv("Data_hackathon.csv")
bank_data
summary(bank_data)
sum(is.na(bank_data))
library(MASS)
library(astsa)

# Create new variable for balance for each month, combination of other variables
bank_data$balance_1 = bank_data$initial_balance + bank_data$deposit_1 - 
  bank_data$loans_1 - bank_data$purchases_1
bank_data$balance_2 = bank_data$balance_1 + bank_data$deposit_2 - 
  bank_data$loans_2 - bank_data$purchases_2
bank_data$balance_3 = bank_data$balance_2 + bank_data$deposit_3 - 
  bank_data$loans_3 - bank_data$purchases_3
bank_data$balance_4 = bank_data$balance_3 + bank_data$deposit_4 - 
  bank_data$loans_4 - bank_data$purchases_4
bank_data$balance_5 = bank_data$balance_4 + bank_data$deposit_5 - 
  bank_data$loans_5 - bank_data$purchases_5
bank_data$balance_6 = bank_data$balance_5 + bank_data$deposit_6 - 
  bank_data$loans_6 - bank_data$purchases_6
bank_data$balance_7 = bank_data$balance_6 + bank_data$deposit_7 - 
  bank_data$loans_7 - bank_data$purchases_7
bank_data$balance_8 = bank_data$balance_7 + bank_data$deposit_8 - 
  bank_data$loans_8 - bank_data$purchases_8
bank_data$balance_9 = bank_data$balance_8 + bank_data$deposit_9 - 
  bank_data$loans_9 - bank_data$purchases_9
bank_data$balance_10 = bank_data$balance_9 + bank_data$deposit_10 - 
  bank_data$loans_10 - bank_data$purchases_10
bank_data$balance_11 = bank_data$balance_10 + bank_data$deposit_11 - 
  bank_data$loans_11 - bank_data$purchases_11
bank_data$balance_12 = bank_data$balance_11 + bank_data$deposit_12 - 
  bank_data$loans_12 - bank_data$purchases_12


# Try some regression, just using initial balance as example, not what we are 
# actually predicting later
fit = lm(initial_balance ~ ., data = bank_data)
fit
summary(fit)

# New equation with significant variables, process seems to work
fit2 = lm(initial_balance ~ balance_1 + deposit_1 + loans_1 + 
          loans_4 + loans_8 + loans_10 + 
          purchases_1 + purchases_2 + purchases_3 + 
          purchases_4 + purchases_5 + purchases_6 + 
          purchases_7 + purchases_8 + purchases_9 + 
          purchases_11 + purchases_12, data = bank_data)
fit2
summary(fit2)

# Stepwise - try actual methods
step.model = stepAIC(fit, direction = "both")


# Try looking at time series, doesn't end up working well
ts = c(bank_data$balance_1, bank_data$balance_2, bank_data$balance_3, 
       bank_data$balance_4, bank_data$balance_5, bank_data$balance_6, 
       bank_data$balance_7, bank_data$balance_8, bank_data$balance_9, 
       bank_data$balance_10, bank_data$balance_11, bank_data$balance_12)
timeseries = ts(ts, frequency = 12, start = 2020)
tsplot(timeseries)
summary(timeseries)

# Maybe try averages, need for graph

averagebal_1 = mean(bank_data$balance_1)
averagebal_2 = mean(bank_data$balance_2)
averagebal_3 = mean(bank_data$balance_3)
averagebal_4 = mean(bank_data$balance_4)
averagebal_5 = mean(bank_data$balance_5)
averagebal_6 = mean(bank_data$balance_6)
averagebal_7 = mean(bank_data$balance_7)
averagebal_8 = mean(bank_data$balance_8)
averagebal_9 = mean(bank_data$balance_9)
averagebal_10 = mean(bank_data$balance_10)
averagebal_11 = mean(bank_data$balance_11)
averagebal_12 = mean(bank_data$balance_12)

xave = c(averagebal_1, averagebal_2, averagebal_3, averagebal_4, averagebal_5, 
         averagebal_6, averagebal_7, averagebal_8, averagebal_9, averagebal_10, 
         averagebal_11, averagebal_12)
timeseriesave = ts(xave, frequency = 12, start = 2020)
tsplot(timeseriesave)
acf1(timeseriesave)

# Thoughts from her
# Not what we are looking for, go re-check variable creation
# So since the variables are simulated and follow normal distributions we can't 
# really do this, if taking averages won't get anything

# Looks like a problem with deposit since it stays constant... maybe change 
# later, idea was it was supposed to be like a paycheck deposited each month







