class State:
    def __init__(self, snake_position: list, food_position: tuple, score: int, game_status: str):
        self.snake_position = snake_position
        self.food_position = food_position
        self.score = score
        self.game_status = game_status

    def to_dict(self):
        return {
            "snake_position": self.snake_position,
            "food_position": self.food_position,
            "score": self.score,
            "game_status": self.game_status
        }
