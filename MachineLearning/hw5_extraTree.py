import csv
import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn import preprocessing
from sklearn.tree import ExtraTreeClassifier
from sklearn.metrics import confusion_matrix


traindata = pd.read_csv("TraData.csv")
traindata = traindata.fillna('0')


traindata = traindata.drop(columns=['adx', 'dclkVerticals'])

for idx in traindata.columns:
    #print(idx)
    """
    app = x['spaceType'] == 'app'                   #0
    site = x['spaceType'] == 'site'                 #1
    spaceid = x['spaceId']                          # 2
    spacecat = x['spaceCat']                        # 3
    adtype = x['adType']                            # 4
    ip = x['ip']                                    # 5
    android = x['os'] == 'Android'                  #6
    blackberry = x['os'] == 'BlackBerry'            #7
    ios = x['os'] == 'iOS'                          #8
    ipad = x['os'] == 'ipad'                        #9
    iphone = x['os'] == 'iphone'                    #10
    linux = x['os'] == 'Linux'                      #11
    mac = x['os'] == 'mac'                          #12
    osx = x['os'] == 'OS X'                         #13    
    others = x['os'] == 'others'                    #14    
    unknown = x['os'] == 'Unknown'                  #15
    windows = x['os'] == 'Windows'                  #16
    wphone = x['os'] == 'Windows Phone'             #17
    phone = x['deviceType'] == 'Phone'              #18
    computer = x['deviceType'] == 'Computer'        #19
    tablet = x['deviceType'] == 'Tablet'            #20
    publisherId = x['publisherId']                  # 21
    campaignId = int(x['campaignId'])               #22
    advertiserId  = int(x['advertiserId'])          #23
    click = x['click'] == '1'                       #24

    data.append([app, site, spaceid, spacecat, adtype, ip, android, blackberry, ios, ipad, iphone,
          linux, mac, osx, others, unknown, windows, wphone, phone, computer, tablet,
          publisherId, campaignId, advertiserId, click])
    
    """
    if idx != 'campaignId' and idx != 'advertiserId' and idx != 'click':
        x = traindata[idx]
        #print(x)
        le = preprocessing.LabelEncoder()
        le.fit(x)
        traindata[idx] = le.transform(x)
    

#data = np.array(data)


print('Finish Label Encode')


clf = ExtraTreeClassifier(random_state=103, splitter='random', max_features=9)

##Get dataset
X = np.array(traindata.iloc[:,:10])
y = np.array(traindata.iloc[:,10])


##build decision tree
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size= 0.1, random_state=11)
clf.fit(X_train, y_train)

print('Finish Extra tree training')

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


testdata = testdata.drop(columns=['adx', 'dclkVerticals'])
##Label Encode
for idx in testdata.columns:
    if idx != 'campaignId' and idx != 'advertiserId' :
        x = testdata[idx]
     #print(x)
    le = preprocessing.LabelEncoder()
    le.fit(x)
    testdata[idx] = le.transform(x)
                    
test_x = np.array(testdata.iloc[:,:10])


pre_x = clf.predict(test_x)
print(pre_x)

countClick = [0, 0]
for i in pre_x :
    if i == 0 :
        countClick[0] += 1
    else :
        countClick[1] += 1

print(countClick)

with open('output9.csv', "w") as output:
    writer = csv.writer(output, lineterminator='\n')
    for val in pre_x:
        writer.writerow([val])

