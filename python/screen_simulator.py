import tkinter as tk
from enum import Enum
import os

class Shapes(Enum):
    RECTANGLE = 0
    BUTTON = 1
    CIRCLE = 2
    LINE = 3
    TEXT = 4

class ScreenSimulator:
    """A simple simulator that allows you to efficiently create pages for the VEX V5 Brain Screen"""
    def __init__(self, root: tk):
        self.root = root
        self.root.title("Screen Simulator")
        self.canvas = tk.Canvas(root, width=480, height=240, bg="white")
        self.canvas.pack(fill=tk.BOTH, expand=True)

        self.setup_bindings()
        self.shapes = []
        self.current_shape = None
        self.shape_type = Shapes.RECTANGLE
        self.selected_shape = None

        self.create_toolbar()

    def create_toolbar(self):
        toolbar = tk.Frame(self.root, bd=1, relief=tk.RAISED)
        toolbar.pack(side=tk.TOP, fill=tk.X)

        rect_btn = tk.Button(toolbar, text="Rect", command=lambda: self.set_shape_type(Shapes.RECTANGLE))
        rect_btn.pack(side=tk.LEFT, padx=2, pady=2)

        btn_btn = tk.Button(toolbar, text="Btn", command=lambda: self.set_shape_type(Shapes.BUTTON))
        btn_btn.pack(side=tk.LEFT, padx=2, pady=2)
        
        circle_btn = tk.Button(toolbar, text="Circ", command=lambda: self.set_shape_type(Shapes.CIRCLE))
        circle_btn.pack(side=tk.LEFT, padx=2, pady=2)
        
        line_btn = tk.Button(toolbar, text="Line", command=lambda: self.set_shape_type(Shapes.LINE))
        line_btn.pack(side=tk.LEFT, padx=2, pady=2)
        
        text_btn = tk.Button(toolbar, text="Text", command=lambda: self.set_shape_type(Shapes.TEXT))
        text_btn.pack(side=tk.LEFT, padx=2, pady=2)

        remove_btn = tk.Button(toolbar, text="Del", command=self.remove_shape)
        remove_btn.pack(side=tk.LEFT, padx=2, pady=2)

        save_btn = tk.Button(toolbar, text="Save", command=self.save_shapes)
        save_btn.pack(side=tk.LEFT, padx=2, pady=2)

        load_btn = tk.Button(toolbar, text="Load", command=self.load_shapes)
        load_btn.pack(side=tk.LEFT, padx=2, pady=2)

    def set_shape_type(self, shape_type):
        self.shape_type = shape_type

    def setup_bindings(self):
        self.canvas.bind("<Button-1>", self.on_canvas_click)
        self.canvas.bind("<B1-Motion>", self.on_canvas_drag)
        self.canvas.bind("<ButtonRelease-1>", self.on_canvas_release)
        self.canvas.bind("<Button-3>", self.on_canvas_right_click)

    def on_canvas_click(self, event):
        self.selected_shape = None
        self.start_x, self.start_y = event.x, event.y
        match self.shape_type:
            case Shapes.RECTANGLE | Shapes.BUTTON:
                self.current_shape = self.canvas.create_rectangle(self.start_x, self.start_y, event.x, event.y, outline="black")
            case Shapes.CIRCLE:
                self.current_shape = self.canvas.create_oval(self.start_x, self.start_y, event.x, event.y, outline="black")
            case Shapes.LINE:
                self.current_shape = self.canvas.create_line(self.start_x, self.start_y, event.x, event.y, fill="black")
            case Shapes.TEXT:

                self.current_shape = self.canvas.create_text(event.x, event.y, text="Sample Text", anchor=tk.NW)

    def on_canvas_drag(self, event):
        if self.current_shape:
            if self.shape_type == Shapes.RECTANGLE or self.shape_type == Shapes.BUTTON:
                self.canvas.coords(self.current_shape, self.start_x, self.start_y, event.x, event.y)
            elif self.shape_type == Shapes.CIRCLE:
                radius = ((event.x - self.start_x) ** 2 + (event.y - self.start_y) ** 2) ** 0.5
                self.canvas.coords(self.current_shape, self.start_x - radius, self.start_y - radius, self.start_x + radius, self.start_y + radius)
            elif self.shape_type == Shapes.LINE:
                self.canvas.coords(self.current_shape, self.start_x, self.start_y, event.x, event.y)

    def on_canvas_release(self, event):
        if self.current_shape:
            if self.shape_type == Shapes.CIRCLE:
                radius = ((event.x - self.start_x) ** 2 + (event.y - self.start_y) ** 2) ** 0.5
                self.shapes.append((self.shape_type, (self.start_x, self.start_y, radius)))
            else:
                self.shapes.append((self.shape_type, self.canvas.coords(self.current_shape)))
            self.current_shape = None

    def on_canvas_right_click(self, event):
        x, y = event.x, event.y
        for shape in self.shapes:
            shape_type, coords = shape
            match shape_type:
                case Shapes.RECTANGLE | Shapes.BUTTON:
                    x1, y1, x2, y2 = coords
                    if x1 <= x <= x2 and y1 <= y <= y2:
                        self.selected_shape = shape
                        break
                case Shapes.CIRCLE:
                    cx, cy, radius = coords
                    if (x - cx) ** 2 + (y - cy) ** 2 <= radius ** 2:
                        self.selected_shape = shape
                        break
                # removing the line currently does not work
                case Shapes.LINE:
                    x1, y1, x2, y2 = coords
                    if x1 <= x <= x2 and y1 <= y <= y2:
                        self.selected_shape = shape
                        break
                case Shapes.TEXT:
                    x1, y1 = coords
                    if x1 <= x <= x1 + 100 and y1 <= y <= y1 + 20:
                        self.selected_shape = shape
                        break

    def remove_shape(self):
        if self.selected_shape:
            self.shapes.remove(self.selected_shape)
            shape_type, coords = self.selected_shape
            if shape_type == Shapes.RECTANGLE or shape_type == Shapes.BUTTON:
                self.canvas.delete(self.canvas.find_closest((coords[0] + coords[2]) / 2, (coords[1] + coords[3]) / 2))
            else:
                self.canvas.delete(self.canvas.find_closest(*coords))
            self.selected_shape = None

    def save_shapes(self):
        shapes = ["rectangle", "button", "circle", "line", "text"]
        file_name = input("File name: ")
        path = os.path.join(os.getcwd(), f"{file_name}.txt")
        with open(path, "w") as file:
            for shape in self.shapes:
                shape_type, coords = shape
                shape_type = shapes[shape_type.value]
                coords = ','.join(map(lambda x: str(int(x)), coords))
                file.write(f"{shape_type},{coords}\n")
        print(f"Drawing saved to {file_name}.txt")

    def load_shapes(self):
        file_name = input("File name: ")
        path = os.path.join(os.getcwd(), f"{file_name}.txt")
        with open(path, "r") as file:
            for line in file:
                shape_type, *coords = line.strip().split(",")
                shape_type = Shapes[shape_type.upper()]
                coords = list(map(int, coords))
                self.shapes.append((shape_type, coords))
                match shape_type:
                    case Shapes.RECTANGLE | Shapes.BUTTON:
                        self.canvas.create_rectangle(*coords, outline="black")
                    case Shapes.CIRCLE:
                        cx, cy, radius = coords
                        self.canvas.create_oval(cx - radius, cy - radius, cx + radius, cy + radius, outline="black")
                    case Shapes.LINE:
                        self.canvas.create_line(*coords, fill="black")
                    case Shapes.TEXT:
                        x, y = coords
                        self.canvas.create_text(x, y, text="Sample Text", anchor=tk.NW)

if __name__ == "__main__":
    root = tk.Tk()
    app = ScreenSimulator(root)
    root.mainloop()
