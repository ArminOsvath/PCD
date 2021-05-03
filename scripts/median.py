import cv2
img = cv2.imread('/home/dj/VSC/C_Cpp/Project/Image.jpg')

#mediana
median = cv2.medianBlur(img,5)
cv2.imwrite("/home/dj/VSC/C_Cpp/Project/images/median.jpg", median)