import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn import preprocessing
from sklearn.tree import DecisionTreeClassifier


traindata = pd.read_csv("TraData.csv")


print(traindata.columns)
print(traindata.index)

X = np.array(traindata.iloc[:,0:12])
y = np.array(traindata.iloc[:,12])

#print(y) 

for i in range(0, 12) :
    x = X[:, i]
    for j in range(0, len(x)) :
        x[j] = str(x[j]) 
    le = preprocessing.LabelEncoder()
    le.fit(x)
    X[:,i] = le.transform(x)
    #print(X[:, i])
                                                                                        

#print(X)
#print(type(y))

X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=0)

clf = DecisionTreeClassifier(max_leaf_nodes=10, random_state=0)
clf.fit(X_train, y_train)

#print(clf.feature_importances_)
print(list(zip(traindata.columns, clf.feature_importances_)))

testdata = pd.read_csv("input.csv")

test_x = np.array(testdata.iloc[:, 0:12])
#test_y = np.array(testdata.iloc[:, 12])



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


