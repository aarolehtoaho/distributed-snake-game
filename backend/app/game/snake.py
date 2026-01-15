class Snake:
    # Directions:
    UP = "up"
    DOWN = "down"
    LEFT = "left"
    RIGHT = "right"

    def __init__(self, position: list, direction: str):
        self.position = position 
        self.direction = direction

    def move(self):
        head_x, head_y = self.position[0]
        if self.direction == Snake.UP:
            new_head = (head_x, head_y - 1)
        elif self.direction == Snake.DOWN:
            new_head = (head_x, head_y + 1)
        elif self.direction == Snake.LEFT:
            new_head = (head_x - 1, head_y)
        else:
            new_head = (head_x + 1, head_y)

        self.position = [new_head] + self.position

    def remove_tail(self) -> tuple[int, int]:
        return self.position.pop()

    def get_direction(self) -> str:
        return self.direction

    def change_direction(self, new_direction: str):
        # Preventing snake from reversing is handled in Input.new_direction()
        self.direction = new_direction
