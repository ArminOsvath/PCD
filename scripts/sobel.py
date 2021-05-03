import cv2
img = cv2.imread('/home/dj/VSC/C_Cpp/Project/Image.jpg')

#sobel
sobel = cv2.Sobel(cv2.cvtColor(img, cv2.COLOR_BGR2GRAY), 5, 1, 1, cv2.BORDER_DEFAULT)
cv2.imwrite("/home/dj/VSC/C_Cpp/Project/images/sobel.jpg", sobel)

