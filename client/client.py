import requests
import renderer

class Client:
    HOST = '127.0.0.1'
    PORT = 8000

    BOARD_WIDTH = 40
    BOARD_HEIGHT = 30

    def __init__(self):
        self.renderer = renderer.Renderer(self.BOARD_WIDTH, self.BOARD_HEIGHT)
        self.state: dict | None = None

    def request_game_state(self) -> dict | None:
        try:
            response = requests.get(f'http://{self.HOST}:{self.PORT}/')
            response.raise_for_status()
            return response.json()
        except requests.RequestException:
            return None

    def update(self):
        self.renderer.clear_screen()
        self.renderer.draw_grid(self.BOARD_HEIGHT, self.BOARD_WIDTH)

        self.state = self.request_game_state()

        if self.state is None:
            self.renderer.draw_text_panel('Server is not available')
            self.renderer.update_display()
            return
        
        food_position: tuple = self.state.get('food_position')
        snake_position: list[tuple] = self.state.get('snake_position')
        score: int = self.state.get('score')
        game_status: str = self.state.get('game_status')

        all_not_null = food_position is not None and \
                       snake_position is not None and \
                       score is not None and \
                       game_status is not None
        if not all_not_null:
            self.renderer.draw_text_panel('Invalid game state received')
            self.renderer.update_display()
            return
        
        self.renderer.draw_square(food_position[1], food_position[0])
        for snake_square in snake_position:
            self.renderer.draw_square(snake_square[1], snake_square[0])
        self.renderer.draw_text_panel(f'Score: {score} | Status: {game_status}')
        self.renderer.update_display()
