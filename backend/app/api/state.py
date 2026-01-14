class State:
    def __init__(self):
        self.snake_position = [(5, 5), (6, 5), (7, 5)]
        self.food_position = (10, 10)
        self.score = 0
        self.game_status = "active"

    def to_dict(self):
        return {
            "snake_position": self.snake_position,
            "food_position": self.food_position,
            "score": self.score,
            "game_status": self.game_status
        }
