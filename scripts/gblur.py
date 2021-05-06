
import cv2
import argparse

scriptVar = '_gblur.'

parser = argparse.ArgumentParser(description ='Description')
parser.add_argument('srvPath')
parser.add_argument('pathToImg')
parser.add_argument('imgName')

args = parser.parse_args()

imgName = args.imgName.split('.')[0]
imgExtension = args.imgName.split('.')[1]
pathToSave = args.srvPath + '/output/' + imgName + scriptVar + imgExtension 

img = cv2.imread(args.pathToImg)
#gaussian
gaussian_blur = cv2.GaussianBlur(img, (15,15), cv2.BORDER_DEFAULT)
cv2.imwrite(pathToSave, gaussian_blur)

