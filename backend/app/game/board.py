from random import choice

class Board:
    # Square types
    EMPTY = 0
    SNAKE = 1
    FOOD = 2
    OUT_OF_BOUNDS = 3

    def __init__(self, width: int, height: int):
        self.width = width
        self.height = height
        self.grid = [[Board.EMPTY for _ in range(width)] for _ in range(height)]

    def place_snake(self, snake_positions: list):
        for x, y in snake_positions:
            self.grid[y][x] = Board.SNAKE

    def place_snake_head(self, head_position: tuple):
        x, y = head_position
        self.grid[y][x] = Board.SNAKE

    def place_food(self, food_position: tuple):
        x, y = food_position
        self.grid[y][x] = Board.FOOD

    def clear_square(self, position: tuple):
        x, y = position
        self.grid[y][x] = Board.EMPTY

    def get_square(self, position: tuple) -> int:
        x, y = position
        if x < 0 or x >= self.width or y < 0 or y >= self.height:
            return Board.OUT_OF_BOUNDS
        return self.grid[y][x]

    def find_empty_square(self) -> tuple | None:
        empty_squares = []
        for y in range(self.height):
            for x in range(self.width):
                if self.grid[y][x] == Board.EMPTY:
                    empty_squares.append((x, y))
        if not empty_squares:
            return None

        return choice(empty_squares)

    def to_string(self):
        representation = ""
        for row in self.grid:
            representation += ' '.join(str(square) for square in row) + "\n"
        return representation
