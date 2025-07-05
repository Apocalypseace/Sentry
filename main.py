import cv2
import numpy as np
import serial
import time

flag = 0
# Initialize serial communication with Arduino
arduino = serial.Serial('COM3', 9600)  # Replace 'COM3' with your Arduino's port
time.sleep(2)  # Wait for Arduino to initialize

# Load YOLOv3 weights and configuration
net = cv2.dnn.readNet(r"C:\Users\adith\Downloads\yolov3-tiny.weights", r"C:\Users\adith\Downloads\yolov3-tiny.cfg")

# Get classes
classes = []
with open(r"C:\Users\adith\Downloads\coco.names", "r") as f:
    classes = [line.strip() for line in f.readlines()]

# Define the output layer names
layer_names = net.getLayerNames()
output_layers = [layer_names[i - 1] for i in net.getUnconnectedOutLayers()]

# Start video capture
cap = cv2.VideoCapture(0)

# Set desired frame width and height
frame_width = 1920
frame_height = 1080

# Set the frame width and height
cap.set(cv2.CAP_PROP_FRAME_WIDTH, frame_width)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, frame_height)

while True:
    ret, frame = cap.read()
    if not ret:
        break

    # Prepare frame for detection
    blob = cv2.dnn.blobFromImage(frame, 1 / 255.0, (320, 320), swapRB=True, crop=False)
    net.setInput(blob)

    # Perform object detection
    detections = net.forward(output_layers)

    # Initialize variables to store the highest confidence detection
    highest_confidence = 0
    best_detection = None

    # Loop over the detections
    for detection in detections:
        for obj in detection:
            scores = obj[5:]
            class_id = np.argmax(scores)
            confidence = scores[class_id]

            # Check if the detected object is a person (class_id for 'person' in COCO dataset is 0)
            if confidence > 0.1 and class_id == 0:  # Lowered the threshold to 0.1
                if confidence > highest_confidence:
                    highest_confidence = confidence
                    best_detection = obj

    if best_detection is not None:
        center_x = int(best_detection[0] * frame_width)
        center_y = int(best_detection[1] * frame_height)
        w = int(best_detection[2] * frame_width)
        h = int(best_detection[3] * frame_height)
        print("x=", center_x)
        print("y=", center_y)

        # Draw bounding box around the person
        cv2.rectangle(frame, (center_x - w // 2, center_y - h // 2),
                      (center_x + w // 2, center_y + h // 2), (0, 255, 0), 2)

        if 900 < center_x < 1000:
            rot = 2
        elif center_x < 900:
            rot = 0
        else:
            rot = 1

        if center_y > 700:
            ro = 0
        elif center_y < 600:
            ro = 1
        else:
            ro = 2

        print(rot)
        print(ro)

        flag = 0

        # Send rotation directions to Arduino via serial communication
    if flag == 0:
        try:
            arduino.write(f"{rot},{ro}\n".encode())
        except Exception as e:
            print("Error sending data to Arduino:", e)
        flag = 1

    # Display output frame
    cv2.imshow('Person Detection', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release resources and close windows
cap.release()
cv2.destroyAllWindows()
arduino.close()
