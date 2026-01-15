from app.api.input import Input
from app.api.state import State
from app.game.board import Board
from app.game.snake import Snake
from app.config import INITIAL_SNAKE_POSITION, INITIAL_FOOD_POSITION, BOARD_HEIGHT, BOARD_WIDTH

class Game:
    def __init__(self):
        self.state = State(INITIAL_SNAKE_POSITION,
                           INITIAL_FOOD_POSITION,
                           0,
                           State.PAUSED)
        self.input = Input()
        self.board = Board(BOARD_WIDTH,
                           BOARD_HEIGHT)
        self.snake = Snake(INITIAL_SNAKE_POSITION,
                           Snake.LEFT)
        self.board.place_snake(self.snake.position)
        self.board.place_food(self.state.food_position)

    def get_state(self):
        return self.state.to_dict()

    def set_input(self, x: float, y: float, button: bool, timestamp: int):
        self.input.update(x, y, button, timestamp)

    def update(self):
        if self.state.game_status != State.RUNNING:
            return

        new_direction = self.input.new_direction(self.snake.get_direction())
        self.snake.change_direction(new_direction)
        self.snake.move()

        new_head = self.snake.position[0]
        next_square = self.board.get_square(new_head)

        match next_square:
            case Board.EMPTY:
                tail = self.snake.remove_tail()
                self.board.clear_square(tail)
            case Board.FOOD:
                self.state.increase_score()
                new_food_position = self.board.find_empty_square()
                if new_food_position:
                    self.state.change_food_position(new_food_position)
                else:
                    self.state.change_game_status(State.GAME_OVER)
            case Board.SNAKE:
                self.state.change_game_status(State.GAME_OVER)
                return

        self.state.change_snake_position(self.snake.position)
        self.board.place_snake(self.snake.position)
        self.board.place_food(self.state.food_position)
