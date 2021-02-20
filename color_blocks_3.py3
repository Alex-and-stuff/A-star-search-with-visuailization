import numpy as np
import cv2
import math

# 建立一張 512x512 的 RGB 圖片（黑色）
img = np.zeros((610, 410, 3), np.uint8)

# 將圖片用淺灰色 (200, 200, 200) 填滿
img.fill(255)

for i in range(41):
	for j in range(61):
		cv2.rectangle(img, (10*i, 10*j), (10*i + 10, 10*j+10), (150, 150, 150), 0)

#cv2.rectangle(img, (10*2, 10*2), (10*2 + 10, 10*2+10), (255, 0, 255), -1)

w_x, h_y = 41, 61;
#maze = [[0 for x in range(w_x)] for y in range(h_y)] 
maze = [[0] * h_y for i in range(w_x)]
wallthick = 1
def BuildMaze():
	w_x, h_y= 41, 61;
	for i in range(w_x):
		for j in range(h_y):
			maze[i][j] = 1
	for i in range(w_x):
		for j in range(wallthick):
			maze[i][j] = 0
			maze[i][h_y - j - 1] = 0
	for i in range(h_y):
		for j in range(wallthick):
			maze[j][i] = 0
			maze[w_x - j - 1][i] = 0
	print(maze)


#===============================================
def DrawMaze(start, goal, maze):
	robotsize = 5
	half_robotsize = int(robotsize/2)
	w_x, h_y = 41, 61;

	#maze[start[0]][start[1]] = 85
	for i in range(robotsize):
		for j in range(robotsize):
			if start[0] - half_robotsize + i >= 0 and start[1] - half_robotsize + j >=0 and start[0] - half_robotsize + i < w_x and start[1] - half_robotsize + j < h_y:
				maze[start[0] - half_robotsize + i][start[1] - half_robotsize + j] = 85

	maze[goal[0]][goal[1]] = 89
	
	for j in range(h_y-1,-1,-1):
		for i in range(w_x):
			'''color = int(math.sqrt(int(maze[i][j])))*10
			if color > 255:
				color = 255
			cv2.rectangle(img, (10*i, 10*j), (10*i + 10, 10*j+10), (255-color, color, color), -1)'''
			if maze[i][j] == 0:
				cv2.rectangle(img, (10*i, 10*j), (10*i + 10, 10*j+10), (204, 102, 0), -1) #wall
			elif maze[i][j] == 88:
				cv2.rectangle(img, (10*i, 10*j), (10*i + 10, 10*j+10), (40, 100, 200), -1)
			elif maze[i][j] == 84:
				#cv2.rectangle(img, (10*i, 10*j), (10*i + 10, 10*j+10), (56, 123, 255), -1)
				cv2.rectangle(img, (10*i, 10*j), (10*i + 10, 10*j+10), (153, 204, 255), -1) #search area
			elif maze[i][j] == 1:
				cv2.rectangle(img, (10*i, 10*j), (10*i + 10, 10*j+10), (200, 200, 200), 1) #blocks
			elif maze[i][j] == 85:
				cv2.rectangle(img, (10*i, 10*j), (10*i + 10, 10*j+10), (56, 50, 200), -1) #start
			elif maze[i][j] == 39:
				cv2.rectangle(img, (10*i, 10*j), (10*i + 10, 10*j+10), (56, 150, 100), -1) #simplified path
			elif maze[i][j] == 89:
				cv2.rectangle(img, (10*i, 10*j), (10*i + 10, 10*j+10), (56, 123, 50), -1) #goal
			elif maze[i][j] == 99:
				cv2.rectangle(img, (10*i, 10*j), (10*i + 10, 10*j+10), (56, 123, 255), -1) #path
			elif maze[i][j] == 50:
				cv2.rectangle(img, (10*i, 10*j), (10*i + 10, 10*j+10), (56, 0, 55), -1)
			elif maze[i][j] == 90:
				cv2.rectangle(img, (10*i, 10*j), (10*i + 10, 10*j+10), (56, 0, 0), -1)
			else:
				cv2.rectangle(img, (10*i, 10*j), (10*i + 10, 10*j+10), (255, 204, 153), -1) #prediction

def DrawLine(start, simple_path):
	new_path = []
	sx = start[0]
	sy = start[1]
	new_path.append((sx, sy))
	for item in simple_path:
		new_path.append(item)
	print(new_path)
	for i in range(len(new_path)-1):
		print(i)
		x = new_path[i][1]*10
		y = new_path[i][0]*10
		xx = new_path[i+1][1]*10
		yy = new_path[i+1][0]*10
		print(str(x) +' '+ str(y) +' '+ str(xx) +' '+ str(yy))
		cv2.line(img, (y, x), (yy, xx), (0, 0, 255), 5)

#===============================================

with open('maze.txt') as textFile:
    # lines = [line.split() for line in textFile]
    lines = []
    for item in [line.split() for line in textFile]:
    	lines.append([int(n) for n in item])
lines= np.flip(lines, 0) 
lines= np.flip(lines, 0) 
print(lines)



start = [int(800/50), int(300/50)]  #x, y  #<---start
goal = [int(1800/50), int(2800/50)]  #x, y #<---goal   
for x in range(41):
	for y in range(61):
		if lines[x][y] == 85:
			start = [x, y] 
			print('found')               
DrawMaze(start, goal, lines)
c = [start, [36,56]]                     #<--b vector
DrawLine(start, c)
# 顯示圖片
#img = cv2.rotate(img, cv2.ROTATE_180)
img = cv2.flip(img, 0)
cv2.imshow('My Image', img)
cv2.imwrite('maze.jpg', img)

# 按下任意鍵則關閉所有視窗
cv2.waitKey(0)
cv2.destroyAllWindows()