import csv
import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn import preprocessing
from sklearn.ensemble import RandomForestClassifier


traindata = pd.read_csv("TraData.csv")

X = np.array(traindata.iloc[:,0:12])
y = np.array(traindata.iloc[:,12])

for i in range(0, 12) :
    x = X[:, i]
    for j in range(0, len(x)) :
        x[j] = str(x[j]) 
    le = preprocessing.LabelEncoder()
    le.fit(x)
    X[:,i] = le.transform(x)
   

clf = RandomForestClassifier(n_estimators=100, n_jobs=3, criterion='entropy', oob_score=True)
clf.fit(X, y)

print(clf.feature_importances_)
print(clf.score(X, y))

testdata = pd.read_csv("input.csv")

test_x = np.array(testdata.iloc[:, 0:12])

for i in range(0, 12) :
    x = test_x[:, i]
    for j in range(0, len(x)) :
        x[j] = str(x[j]) 
    le = preprocessing.LabelEncoder()
    le.fit(x)
    test_x[:,i] = le.transform(x)

pre_x = clf.predict(test_x)
print(pre_x)

countClick = [0, 0]
for i in pre_x :
    if i == 0 :
        countClick[0] += 1
    else :
        countClick[1] += 1

print(countClick)

with open('output4.csv', "w") as output:
  writer = csv.writer(output, lineterminator='\n')
  for val in pre_x:
    writer.writerow([val])