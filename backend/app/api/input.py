from math import atan2

class Input:
    opposite_directions = {"up": "down", "down": "up", "left": "right", "right": "left"}

    def __init__(self):
        self.x = 0.5
        self.y = 0.5
        self.button = False
        self.timestamp = 0

    def update(self, x: float, y: float, button: bool, timestamp: int):
        self.x = x
        self.y = y
        self.button = button
        self.timestamp = timestamp

    def new_direction(self, current_direction: str) -> str:
        tilt_length = ((self.x - 0.5) ** 2 + (self.y - 0.5) ** 2) ** 0.5
        if tilt_length < 0.2:
            return current_direction

        angle = atan2(self.y - 0.5, self.x - 0.5)
        direction = ""
        if -3.14 / 4 <= angle < 3.14 / 4:
            direction = "right"
        elif 3.14 / 4 <= angle < 3 * 3.14 / 4:
            direction = "up"
        elif -3 * 3.14 / 4 <= angle < -3.14 / 4:
            direction = "down"
        else:
            direction = "left"

        if direction == current_direction:
            return current_direction

        if direction == self.opposite_directions.get(current_direction):
            return current_direction

        return direction
