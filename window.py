from tkinter import *
import boardWrapper

boardpeice = boardWrapper.PyPiece()


root = Tk()

b = 0
a  = 'a'
for i in range(19):
    for j in range(19):
        b = b + 1

        Button(root, text = a + str(b), borderwidth = 1).grid(row = i, column = j)

def printcoords(event):
    print (event.x, event.y)

#canvas.bind("<button 1>", printcoords)

root.mainloop()
