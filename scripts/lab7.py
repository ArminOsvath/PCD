import cv2;
import numpy as np;
OG = cv2.imread('/home/dj/VSC/C_Cpp/Project/Image.jpg',0)

#kernel
kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (2,2))
#dilatare
dilate = cv2.dilate(OG, kernel)
#eroziune
erode = cv2.erode(OG, kernel)
#final
image = cv2.absdiff(dilate, erode)

img = cv2.imread("/home/dj/VSC/C_Cpp/Project/Image.jpg")
img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

#margini
edged = cv2.Canny(img_gray, 50, 150)
#contur
contours, hierarchy = cv2.findContours(edged.copy(), cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)
fill_contour = edged.copy()
#umplere
for contour in contours:
    cv2.fillPoly(fill_contour, pts=[contour], color=(255,255,255))

cv2.imshow("Culloare contur", fill_contour)
cv2.imshow("Extragere", image)
cv2.imshow("Original", img)
cv2.imwrite("Contur_L7.jpg", image)
cv2.imwrite("Fill_L7.jpg", fill_contour)

cv2.waitKey(0)