
import cv2
img = cv2.imread('/home/dj/VSC/C_Cpp/Project/Image.jpg')
#blur 5x5
blur = cv2.blur(img, ksize=(5,5), borderType=cv2.BORDER_DEFAULT)
#gaussian
gaussian_blur = cv2.GaussianBlur(img, (15,15), cv2.BORDER_DEFAULT)
#sobel
sobel = cv2.Sobel(cv2.cvtColor(img, cv2.COLOR_BGR2GRAY), 5, 1, 1, cv2.BORDER_DEFAULT)
#mediana
median = cv2.medianBlur(img,5)

cv2.imshow('Source image', img)

cv2.imshow('blur 5x5', blur)
cv2.imwrite("L9_blur.jpg", blur)

cv2.imwrite("L9_Gblur.jpg", gaussian_blur)
cv2.imshow('gaussian_blur', gaussian_blur)

cv2.imwrite("L9_sobel.jpg", sobel)
cv2.imshow('sobel', sobel)

cv2.imshow('median', median)
cv2.imwrite("L9_median.jpg", median)

cv2.waitKey()
