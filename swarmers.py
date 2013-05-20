#!/usr/bin/python

import sys
import pyglet
import random
from math import sqrt

window = pyglet.window.Window(resizable=True)

batch = pyglet.graphics.Batch()
mousepos = [0, 0, 0]
makingSwarmers = False
killingSwarmers = False
class Swarmer:
	def __init__(self, random=False):
		self.x = 320
		self.y = 240
		if random:
			self.x = random.randrange(640)
			self.y = random.randrange(480)

		
		self.speed = 5
		self.length = 20
		self.vlist = batch.add(2, pyglet.gl.GL_LINES, None,
			('v2f', (self.x, self.y, self.x, self.y+self.length)),
			('c3B', (255, 0, 0, 0, 0, 0))
		)
	def update(self):
		diffx = mousepos[0] - self.x
		diffy = mousepos[1] - self.y
		diffT = sqrt(diffx**2 + diffy**2)
		if mousepos[2] == 0:
			self.x += (diffx/diffT)*self.speed + random.randrange(10)/50.
			self.y += (diffy/diffT)*self.speed + random.randrange(10)/50.
			pbx, pby = self.x - (diffx/diffT)*self.length, self.y - (diffy/diffT)*self.length
		else:
			self.x -= (diffx/diffT)*self.speed + random.randrange(10)/50.
			self.y -= (diffy/diffT)*self.speed + random.randrange(10)/50.
			pbx, pby = self.x + (diffx/diffT)*self.length, self.y + (diffy/diffT)*self.length
		
		self.vlist.vertices = [self.x, self.y, pbx, pby]
	def __del__(self):
		self.vlist.delete()

swarmerlist = []
for i in range(750):
	swarmerlist.append(Swarmer())
pyglet.gl.glClearColor(0, 0, 0.8, 0)
pyglet.gl.glLineWidth(3)
fps_display = pyglet.clock.ClockDisplay()
countDesc = pyglet.text.Label('Swarmer Count:',
                          font_size=13,
                          x=0, y=0,
                          anchor_x='left', anchor_y='bottom')

countValue = pyglet.text.Label('1',
                          font_size=13,
                          x=140, y=0,
                          anchor_x='left', anchor_y='bottom')


@window.event
def on_draw():
	window.clear()
	batch.draw()
	fps_display.draw()
	countDesc.draw()
	countValue.draw()

@window.event
def on_mouse_motion(x, y, dx, dy):
	global mousepos
	mousepos = [x, y, 0]

@window.event
def on_mouse_drag(x, y, dx, dy, button, mods):
	global mousepos
	if button == pyglet.window.mouse.LEFT:
		mousepos = [x, y, 1]
	else:
		mousepos = [x, y, 0]

@window.event
def on_mouse_press(x, y, button, mods):
	if button == pyglet.window.mouse.LEFT:
		mousepos[2] = 1
	elif button == pyglet.window.mouse.MIDDLE:
		global killingSwarmers
		killingSwarmers = True
	elif button == pyglet.window.mouse.RIGHT:
		global makingSwarmers
		makingSwarmers = True

@window.event
def on_mouse_release(x, y, button, modifiers):
	if button == pyglet.window.mouse.LEFT:
		mousepos[2] = 0
	elif button == pyglet.window.mouse.MIDDLE:
		global killingSwarmers
		killingSwarmers = False
	elif button == pyglet.window.mouse.RIGHT:
		global makingSwarmers
		makingSwarmers = False

@window.event
def on_key_press(key, mods):
	if key == pyglet.window.key.F11:
		window.set_fullscreen(not window.fullscreen)

def update(*args):
	window.clear()
	if killingSwarmers:
		try:
			swarmerlist.pop()
			countValue.text = str(len(swarmerlist))
		except:
			pass
	if makingSwarmers:
		swarmerlist.append(Swarmer())
		countValue.text = str(len(swarmerlist))
	for s in swarmerlist:
		s.update()
	on_draw()
pyglet.clock.schedule(update, 60)

pyglet.app.run()
