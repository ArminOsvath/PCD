import cv2
import argparse

scriptVar = '_gray.'

parser = argparse.ArgumentParser(description ='Description')
parser.add_argument('srvPath')
parser.add_argument('pathToImg')
parser.add_argument('imgName')

args = parser.parse_args()

imgName = args.imgName.split('.')[0]
imgExtension = args.imgName.split('.')[1]
pathToSave = args.srvPath + '/output/' + imgName + scriptVar + imgExtension 

img = cv2.imread(args.pathToImg)

gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
cv2.imwrite(pathToSave, gray)