from app.api.input import Input
from app.api.state import State
from app.config import INITIAL_SNAKE_POSITION

class Game:
    def __init__(self):
        self.state = State(INITIAL_SNAKE_POSITION, (10, 10), 0, "paused")
        self.input = Input()

    def get_state(self):
        return self.state.to_dict()

    def set_input(self, x: float, y: float, button: bool, timestamp: int):
        self.input.update(x, y, button, timestamp)
