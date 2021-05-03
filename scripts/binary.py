import cv2

img = cv2.imread('/home/dj/VSC/C_Cpp/Project/Image.jpg')

gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
(thresh, blackAndWhiteImage) = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY)

cv2.imwrite("/home/dj/VSC/C_Cpp/Project/images/BW.jpg", blackAndWhiteImage)
