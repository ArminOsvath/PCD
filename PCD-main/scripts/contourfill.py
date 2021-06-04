import cv2;
import numpy as np;
import argparse

scriptVar1 = '_contour.'
scriptVar2 = '_fill.'


parser = argparse.ArgumentParser(description ='Description')
parser.add_argument('srvPath')
parser.add_argument('pathToImg')
parser.add_argument('imgName')

args = parser.parse_args()

imgName = args.imgName.split('.')[0]
imgExtension = args.imgName.split('.')[1]
pathToSave1 = args.srvPath + '/output/' + imgName + scriptVar1 + imgExtension 
pathToSave2 = args.srvPath + '/output/' + imgName + scriptVar2 + imgExtension 

img = cv2.imread(args.pathToImg)

#kernel
kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (2,2))
#dilatare
dilate = cv2.dilate(img, kernel)
#eroziune
erode = cv2.erode(img, kernel)
#final
image = cv2.absdiff(dilate, erode)

img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

#margini
edged = cv2.Canny(img_gray, 50, 150)
#contur
contours, hierarchy = cv2.findContours(edged.copy(), cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)
fill_contour = edged.copy()
#umplere
for contour in contours:
    cv2.fillPoly(fill_contour, pts=[contour], color=(255,255,255))

cv2.imwrite(pathToSave1, image)
cv2.imwrite(pathToSave2, fill_contour)

cv2.waitKey(0)