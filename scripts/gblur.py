
import cv2
img = cv2.imread('/home/dj/VSC/C_Cpp/Project/Image.jpg')

#gaussian
gaussian_blur = cv2.GaussianBlur(img, (15,15), cv2.BORDER_DEFAULT)
cv2.imwrite("/home/dj/VSC/C_Cpp/Project/images/Gblur.jpg", gaussian_blur)

