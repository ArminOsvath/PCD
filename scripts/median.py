import cv2
import argparse

scriptVar = '_median.'

parser = argparse.ArgumentParser(description ='Description')
parser.add_argument('srvPath')
parser.add_argument('pathToImg')
parser.add_argument('imgName')

args = parser.parse_args()

imgName = args.imgName.split('.')[0]
imgExtension = args.imgName.split('.')[1]
pathToSave = args.srvPath + '/output/' + imgName + scriptVar + imgExtension 


img = cv2.imread(args.pathToImg)

#mediana
median = cv2.medianBlur(img,5)
cv2.imwrite(pathToSave, median)