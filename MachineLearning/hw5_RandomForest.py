import csv
import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn import preprocessing
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import confusion_matrix


traindata = pd.read_csv("TraData.csv")
traindata = traindata.fillna('0')

##Label Encode
for idx in traindata.columns:
    if idx != 'campaignId' and idx != 'advertiserId' and idx != 'click':
        x = traindata[idx]
        #print(x)
        le = preprocessing.LabelEncoder()
        le.fit(x)
        traindata[idx] = le.transform(x)

print('Finish Label Encode')


##Get dataset
X = np.array(traindata.iloc[:,0:12])
y = np.array(traindata.iloc[:,12])


##build decision tree
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size= 0.1, random_state=10)
clf = RandomForestClassifier(n_estimators=80, n_jobs=3, random_state=39, criterion='entropy')
clf.fit(X_train, y_train)

print('Finish RF training')

predicttest = clf.predict(X_test)

##count click (0 or 1)
countClick = [0, 0]
for i in predicttest :
    if i == 0 :
        countClick[0] += 1
    else :
        countClick[1] += 1

print(countClick)

##get accuracy, precision, recall, f_measure
tn, fp, fn, tp = confusion_matrix(y_test, predicttest).ravel()
print('tp: {0}, tn: {1}, fp: {2}, fn: {3}'.format(tp, tn, fp, fn))
acc = float((tp + tn) / (tp + tn + fp + fn))
precision = float(tp / (tp + fp))
recall = float(tp / (tp + fn))
f_measure =  float(2 * precision * recall / (precision + recall))
print('Accuracy: {0}'.format(acc))
print('Precision: {0}'.format(precision))
print('Recall: {0}'.format(recall))
print('F-measure: {0}'.format(f_measure))


testdata = pd.read_csv("input.csv")
testdata = testdata.fillna('0')

##Label Encode
for idx in testdata.columns:
    if idx != 'campaignId' and idx != 'advertiserId' :
        x = testdata[idx]
        #print(x)
        le = preprocessing.LabelEncoder()
        le.fit(x)
        testdata[idx] = le.transform(x)
        
test_x = np.array(testdata.iloc[:, 0:12])


pre_x = clf.predict(test_x)
print(pre_x)

countClick = [0, 0]
for i in pre_x :
    if i == 0 :
        countClick[0] += 1
    else :
        countClick[1] += 1

print(countClick)
"""
with open('output4.csv', "w") as output:
  writer = csv.writer(output, lineterminator='\n')
  for val in pre_x:
    writer.writerow([val])
"""
