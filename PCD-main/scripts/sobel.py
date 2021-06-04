import cv2
import argparse

scriptVar = '_sobel.'

parser = argparse.ArgumentParser(description ='Description')
parser.add_argument('srvPath')
parser.add_argument('pathToImg')
parser.add_argument('imgName')

args = parser.parse_args()

imgName = args.imgName.split('.')[0]
imgExtension = args.imgName.split('.')[1]
pathToSave = args.srvPath + '/output/' + imgName + scriptVar + imgExtension 

img = cv2.imread(args.pathToImg)
#sobel
sobel = cv2.Sobel(cv2.cvtColor(img, cv2.COLOR_BGR2GRAY), 5, 1, 1, cv2.BORDER_DEFAULT)
cv2.imwrite(pathToSave, sobel)

