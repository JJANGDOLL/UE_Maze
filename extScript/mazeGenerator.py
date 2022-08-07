import pdb
import random

class MazeNode:
	def __init__(self, InVisited = False):
		self.wall = []
		self.isVisited = InVisited
		self.nextWay = [(-1, 0, 'N'), (1, 0, 'S'), (0, -1, 'W'), (0, 1, 'E')]

	def addWall(self, InWay):
		self.wall.append(InWay)

	def prevRoute(self, InDir):
		if InDir == 'N':
			del self.nextWay[1]
		if InDir == 'S':
			del self.nextWay[0]
		if InDir == 'W':
			del self.nextWay[3]
		if InDir == 'E':
			del self.nextWay[2]

	def __str__(self):
		r = ''
		if self.isVisited:
			r = 'T'
		else:
			r = 'F'
		return r + ''.join(self.wall)



class Maze:
	def __init__(self, InSize):
		self.mapSize = InSize + 2
		self.mapNode = {}

		for c in range(self.mapSize):
			for r in range(self.mapSize):
				if r == 0 or r == self.mapSize-1 or c == 0 or c == self.mapSize-1:
					self.mapNode[(c, r)] = MazeNode(True)
				else:
					self.mapNode[(c, r)] = MazeNode()

	def show(self):
		print(self.mapSize)
		for i in range(self.mapSize):
			print(f'{i:<7}',end='')
		print()
		for c in range(self.mapSize):
			for r in range(self.mapSize):
				print(f'{self.mapNode[(c, r)]}'.ljust(6), end=' ')
			print()

	def generate(self):
		dfs = [(1, 1)]
		while dfs:
			if not self.mapNode[dfs[-1]].nextWay:
				dfs.pop()
				continue
			#print(dfs)
			#print(dfs[-1])
			#print(self.mapNode[dfs[-1]].nextWay)
			#m.show()
			#pdb.set_trace()
			self.mapNode[dfs[-1]].isVisited = True
			random.shuffle(self.mapNode[dfs[-1]].nextWay)

			while self.mapNode[dfs[-1]].nextWay:
				nw = self.mapNode[dfs[-1]].nextWay.pop()
				npos = (dfs[-1][0] + nw[0], dfs[-1][1] + nw[1])
				if self.mapNode[npos].isVisited:
					self.mapNode[dfs[-1]].addWall(nw[2])
				else:
					dfs.append(npos)
					self.mapNode[dfs[-1]].prevRoute(nw[2])
					break

m = Maze(4)
m.generate()
m.show()
pdb.set_trace()