class State:
    # Game status types:
    PAUSED = "paused"
    RUNNING = "running"
    GAME_OVER = "game_over"

    def __init__(self, snake_position: list, food_position: tuple, score: int, game_status: str):
        self.snake_position = snake_position
        self.food_position = food_position
        self.score = score
        self.game_status = game_status

    def increase_score(self):
        self.score += 1

    def change_game_status(self, new_status: str):
        self.game_status = new_status

    def change_food_position(self, new_position: tuple):
        self.food_position = new_position

    def change_snake_position(self, new_position: list):
        self.snake_position = new_position

    def to_dict(self):
        return {
            "snake_position": self.snake_position,
            "food_position": self.food_position,
            "score": self.score,
            "game_status": self.game_status
        }
