import cv2
import argparse

scriptVar = '_eqhis.'

parser = argparse.ArgumentParser(description ='Description')
parser.add_argument('srvPath')
parser.add_argument('pathToImg')
parser.add_argument('imgName')

args = parser.parse_args()

imgName = args.imgName.split('.')[0]
imgExtension = args.imgName.split('.')[1]
pathToSave = args.srvPath + '/output/' + imgName + scriptVar + imgExtension 

img = cv2.imread(args.pathToImg)
# citire
# culoare -> grey
src = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
# functia de egalizare
dst = cv2.equalizeHist(src)

cv2.imwrite(pathToSave, dst)
