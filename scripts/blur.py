
import cv2
img = cv2.imread('/home/dj/VSC/C_Cpp/Project/Image.jpg')

#blur 5x5
blur = cv2.blur(img, ksize=(5,5), borderType=cv2.BORDER_DEFAULT)
cv2.imwrite("/home/dj/VSC/C_Cpp/Project/images/blur.jpg", blur)


cv2.waitKey()
