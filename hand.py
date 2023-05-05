from cvzone.HandTrackingModule import HandDetector
import cvzone
import serial
import cv2

cap = cv2.VideoCapture(1)
detector = HandDetector(maxHands=1, detectionCon=0.7)
mySerial = serial.Serial(port="COM7", baudrate=2038, timeout=1)

while True:
    success, img = cap.read()
    img = detector.findHands(img)
    lmList, bbox = detector.findPosition(img)
    if (lmList):
        fingers = detector.fingersUp()
        print(fingers)
        mySerial.sendData(fingers)
    cv2.imshow("Image", img)
    cv2.waitKey(1)