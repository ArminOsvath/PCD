
import cv2
import argparse

scriptVar = '_blur.'

parser = argparse.ArgumentParser(description ='Description')
parser.add_argument('srvPath')
parser.add_argument('pathToImg')
parser.add_argument('imgName')

args = parser.parse_args()

imgName = args.imgName.split('.')[0]
imgExtension = args.imgName.split('.')[1]
pathToSave = args.srvPath + '/output/' + imgName + scriptVar + imgExtension 

img = cv2.imread(args.pathToImg)

#blur 5x5
blur = cv2.blur(img, ksize=(5,5), borderType=cv2.BORDER_DEFAULT)
cv2.imwrite(pathToSave, blur)


cv2.waitKey()
